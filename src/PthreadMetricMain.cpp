/*
 * PthreadMetricMain.cpp
 *
 *  Created on: Apr 26, 2014
 *      Author: Sisi
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <tr1/unordered_set>
#include <tr1/unordered_map>
#include <pthread.h>
//#include <stdexcept>
// #include "rdtsc.h"
#include "cmdline.h"
#include "PthreadMetric.cpp"

// #define MAIN_DEBUG
#define GANXIS_MACHINE 1
//#define GANXIS_CLOCK_RATE 2100000000
//#define GANXIS_CLOCK_RATE_BACKUP 2100000000
#define BLUE_GENE_Q_CLOCK_RATE 1600000000
//#define KRATOS_CLOCK_RATE 2667000000

using namespace std;
using namespace std::tr1;

double evalClockRate()
{
	// TODO: lscpu call can be used and "PU MHz:    2146.278" parsing from the results
	return 2100000000;
}

int main(int argc, char **argv) {
	// Parse the input arguments
	gengetopt_args_info  args_info;
	auto  err = cmdline_parser(argc, argv, &args_info);
	if(err)
		return err;

	// Validate the input arguments
	if(args_info.inputs_num != 2) {
		string files;
		for(unsigned i = 0; i < args_info.inputs_num; ++i)
			files.append(args_info.inputs[i]).append(" ");
		cerr << "ERROR, 2 input files are expected instead of " << args_info.inputs_num << ": " << files << endl;
		return EINVAL;
	}
	if(args_info.cpufreq_arg <= 0) {
		cerr << "ERROR, positive CPU frequency is expected: " << args_info.cpufreq_arg << endl;
		//throw invalid_argument("Positive CPU frequency is expected");
		return EINVAL;
	}
	const double  GANXIS_CLOCK_RATE = double(args_info.cpufreq_arg) * 1E6;
	// The first parameter decide what's kind of metric shall we compute:
	// 1---with ground truth or 0---without ground truth
	if(args_info.num_arg <= 0) {
		cerr << "ERROR, positive number of threads is expected: " << args_info.num_arg << endl;
		return EINVAL;
	}
	const int numThreads = args_info.num_arg;  // atoi(argv[1]);

	//int metricType = atoi(argv[2]);
	//if (metricType)
	if(args_info.extrinsic_given) {
		//if (argc != 5) {
		//	fprintf(stderr,"Usage: %s numThreads metricType realCommunityFile detectedCommunityFile\n", argv[0]);
		//	return 0;
		//}
		string realCommunityFile = args_info.inputs[0];  // argv[3];
		string disCommunityFile = args_info.inputs[1];  // argv[4];

		cout << "Executing in " << numThreads << " threads...\n";
		PthreadMetric<int> pthreadMetric(numThreads, realCommunityFile,
				disCommunityFile, args_info.extrinsic_arg);
		if(args_info.extrinsic_arg == extrinsic_arg_all) {
			double entropyExeCycle = pthreadMetric.computeInfoEntropyMetric();
			double entropyExeTime;
			if (GANXIS_MACHINE) {
				// ganxis machine
				entropyExeTime = entropyExeCycle / GANXIS_CLOCK_RATE;
			} else {
				// Blue Gene/Q
				entropyExeTime = entropyExeCycle / BLUE_GENE_Q_CLOCK_RATE;
			}
			double VI = pthreadMetric.getVI();
			double NMI = pthreadMetric.getNMI();
			cout << "Entropy metric timings: " << entropyExeTime << ";  VI: " << VI << ", NMI: " << NMI << endl;
		}

		if(args_info.extrinsic_arg == extrinsic_arg_all || args_info.extrinsic_arg == extrinsic_arg_f1m
		|| args_info.extrinsic_arg == extrinsic_arg_nvd) {
			double clusteringExeCycle = pthreadMetric.computeClusterMatchingMetric(args_info.extrinsic_arg);
			double clusteringExeTime;
			if (GANXIS_MACHINE) {
				// ganxis machine
				clusteringExeTime = clusteringExeCycle / GANXIS_CLOCK_RATE;
			} else {
				// Blue Gene/Q
				clusteringExeTime = clusteringExeCycle / BLUE_GENE_Q_CLOCK_RATE;
			}
			double fMeasure = pthreadMetric.getFMeasure();
			double NVD = pthreadMetric.getNVD();
			cout << "Cluster metric timings: " << clusteringExeTime << ";  F1-measure: " << fMeasure << ", NVD: " << NVD << endl;
		}

		if(args_info.extrinsic_arg == extrinsic_arg_all || args_info.extrinsic_arg == extrinsic_arg_index) {
			double indexExeCycle = pthreadMetric.computeIndexMetric();
			double indexExeTime;
			if (GANXIS_MACHINE) {
				// ganxis machine
				indexExeTime = indexExeCycle / GANXIS_CLOCK_RATE;
			} else {
				// Blue Gene/Q
				indexExeTime = indexExeCycle / BLUE_GENE_Q_CLOCK_RATE;
			}
			double RI = pthreadMetric.getRI();
			double ARI = pthreadMetric.getARI();
			double JI = pthreadMetric.getJI();
			cout << "Index metric timings: " << indexExeTime << ";  RI: " << RI << ", ARI: " << ARI << ", JI: " << JI << endl;
		}
		//cout << numThreads << "\t" << entropyExeTime << "\t" << clusteringExeTime << "\t" << indexExeTime << endl;
		//cout << numThreads << "\t" << VI << "\t" << NMI << "\t" << fMeasure << "\t" << NVD << "\t" << RI << "\t" << ARI << "\t" << JI << endl;
	}
	// For metric without ground truth communities
	else if(args_info.intrinsic_given) {
		//if (argc < 5) {
		//	fprintf(stderr,"Usage: %s numThreads metricType detectedCommunityFile networkFile [isUnweighted isUndirected]\n", argv[0]);
		//	return 0;
		//}
		string networkFile = args_info.inputs[0];  // argv[4];
		string disCommunityFile = args_info.inputs[1];  // argv[3];
		const bool isUnweighted = !args_info.weighted_flag;
		// true;
		//if (argc > 5) {
		//	isUnweighted = atoi(argv[5]);
		//}
		const bool isUndirected = !args_info.directed_flag;
		// true;
		//if (argc > 6) {
		//	isUndirected = atoi(argv[6]);
		//}

		PthreadMetric<int> pthreadMetric(numThreads, networkFile, isUnweighted,
				isUndirected, disCommunityFile, args_info.intrinsic_arg);
		double exeCycle = pthreadMetric.computeMetricWithoutGroundTruth();
		double exeTime;
		if (GANXIS_MACHINE) {
			// ganxis machine
			exeTime = exeCycle / GANXIS_CLOCK_RATE;
		} else {
			// Blue Gene/Q
			exeTime = exeCycle / BLUE_GENE_Q_CLOCK_RATE;
		}
		double modularity = pthreadMetric.getModularity();
		double Qds = pthreadMetric.getQds();
		double intraEdges = pthreadMetric.getIntraEdges();
		double intraDensity = pthreadMetric.getIntraDensity();
		double contraction = pthreadMetric.getContraction();
		double interEdges = pthreadMetric.getInterEdges();
		double expansion = pthreadMetric.getExpansion();
		double conductance = pthreadMetric.getConductance();
		cout << "Intrinsic metric timings: " << exeTime << ";  Q: " << modularity << ", Qds: "
			<< Qds << ", intraEdges: " << intraEdges << ", intraDensity: " << intraDensity
			<< ", contraction: " << contraction << ", interEdges: " << interEdges
			<< ", expansion: " << expansion << ", conductance: " << conductance << endl;
		//cout << numThreads << "\t" << exeTime << endl;
		//cout << numThreads << "\t" << modularity << "\t" << Qds << "\t" << intraEdges << "\t"
		//<< intraDensity << "\t" << contraction << "\t" << interEdges << "\t" << expansion
		//<< "\t" << conductance << endl;
	}

	return 0;
}

