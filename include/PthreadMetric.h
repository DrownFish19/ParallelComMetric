/*
 * PthreadMetric.h
 *
 *  Created on: Apr 26, 2014
 *      Author: Sisi
 */

#ifndef PTHREADMETRIC_H_
#define PTHREADMETRIC_H_

#include <iostream>
#include <cmath>
#include <cstddef>
#include <string>
#include <vector>
#include <pthread.h>
#include <tr1/unordered_set>
#include <tr1/unordered_map>
// #include "rdtsc.h"
#include "Reader.hpp"
#include "mm.h"
#include "cmdline.h"

using namespace std;
using namespace std::tr1;

template<class T> class PthreadMetric;

template<typename T>
struct thread_arg {
	unsigned int threadId;
	PthreadMetric<T>* classPointer;
};

template<class T>
class PthreadMetric {
private:
	unsigned int numThreads;

	// Network properties
	bool isUnweighted;
	bool isUndirected;

	// Network and community file name
	string networkFile;
	string realCommunityFile;
	string disCommunityFile;

	// Network and community containers
	unordered_map<T, unordered_map<T, double> > network;
	unordered_map<T, unordered_map<T, double> > inNet;
	vector<unordered_set<T> > realVecCommunities;
	vector<unordered_set<T> > disVecCommunities;
	unordered_map<T, int> realMapCommunities;
	unordered_map<T, int> disMapCommunities;

	// The total number of nodes in the network or in the community
	long numNodes;

	// The total weights of all the edges in the network
	double totalWeight;

	// metrics without ground truth
	double modularity;
	double Qds;
	double intraEdges;
	double intraDensity;
	double contraction;
	double interEdges;
	double expansion;
	double conductance;

	// Information Entropy metrics
	double xentropy;
	double yentropy;
	double VI;
	double NMI;

	// Clustering Matching metrics
	double fMeasure;
	double NVD;

	// Index Metrics
	double a11;
	double a00;
	double a10;
	double a01;
	double RI;
	double ARI;
	double JI;

	// What metrics should be evaluated
	enum_extrinsic  emetrics;
	enum_intrinsic  imetrics;

	int getIntersectionNum(unordered_set<T>& scomm, unordered_set<T>& gcomm);

	static void *metricWithoutGroundTruthAdaptor(void *arg);
	void *subWithoutGroundTruthMetricCalculation(struct thread_arg<T> *arg);

	static void *infoEntropyMetricAdaptor(void *arg);
	void *subInfoEntropyMetricCalculation(struct thread_arg<T> *arg);

	static void *clusterMatchingMetricAdaptor(void *arg);
	void *subClusterMatchingMetricCalculation(struct thread_arg<T> *arg);

	static void *indexMetricAdaptor(void *arg);
	void *subIndexMetricCalculation(struct thread_arg<T> *arg);
public:
	PthreadMetric();
	PthreadMetric(int numThreads, string networkFile, bool isUnweighted,
			bool isUndirected, string disCommunityFile, enum_intrinsic imetrics=intrinsic_arg_all);
	PthreadMetric(int numThreads, string realCommunityFile,
			string disCommunityFile, enum_extrinsic emetrics=extrinsic_arg_all);

	double getModularity();
	double getQds();
	double getIntraEdges();
	double getIntraDensity();
	double getContraction();
	double getInterEdges();
	double getExpansion();
	double getConductance();

	double getVI();
	double getNMI();
	double getFMeasure();
	double getNVD();
	double getRI();
	double getARI();
	double getJI();

	bool isF1m() const  { return emetrics == extrinsic_arg_all || emetrics == extrinsic_arg_f1m; }
	bool isNVD() const  { return emetrics == extrinsic_arg_all || emetrics == extrinsic_arg_nvd; }

	double computeMetricWithoutGroundTruth(enum_intrinsic metrics=intrinsic_arg_all);
	double computeInfoEntropyMetric(enum_extrinsic metrics=extrinsic_arg_all);
	double computeClusterMatchingMetric(enum_extrinsic metrics=extrinsic_arg_all);
	double computeIndexMetric(enum_extrinsic metrics=extrinsic_arg_all);

	~PthreadMetric();
};

#endif /* PTHREADMETRIC_H_ */
