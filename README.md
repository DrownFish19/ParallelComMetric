# ParallelComMetric
A parallel toolkit, implemented with Pthreads (or MPI), to calculate the community quality metrics with and without ground truth community structure.  
The original version is extended with the GNU-style arguments parsing, selective evaluation of the quality measures and the standard Makefile by Artem Lutov <artem@exascale.info>. The extension is licensed under the [Apache License v.2](https://www.apache.org/licenses/LICENSE-2.0), about the license of the original code please ask the initial authors.

Authors: Mingming Chen <mileschen2008@gmail.com> and Sisi Liu <liusisiapply@gmail.com>.  
Collaborator: Boleslaw K. Szymanski <szymab@rpi.edu>.  
Please email comments and suggestions to Mingming Chen <mileschen2008@gmail.com> and Sisi Liu <liusisiapply@gmail.com>.

Paper: `Mingming Chen, Sisi Liu, and Boleslaw Szymanski, “Parallel Toolkit for Measuring the Quality of Network Community Structure”, The First European Network Intelligence Conference (ENIC), Wroclaw, Poland, September, 2014, pp. 22-29.`

## Content
- [Usage](#usage)
- [Compilation](#compilation)
- [Related Projects](#related-projects)

## Usage
```
$ ./bin/Release/pcomet -h
Usage: pcomet [OPTIONS] ground-truth|ipnut-network clustering

  ground-truth  - ground-truth clustering (communities) for the extrinsic
metrics
 evaluation. The clusterins are specified in the NCL format, where each line
consists
 of the member node ids of the respective cluster (community).
  ipnut-network  - input network for the intrinsic metrics evaluation. The
input
 network is specified in the NSL format, where each line describes the
respective
 link: <src_id> <dst_id> [<weight>].
  clustering  - input file, collection of the clusters (detected communities)
to
 be evaluated. in the NCL format, where each line list member node ids of the
 respective cluster (community).
  
Examples:
  $ ./pcomet -n 4 -ef1m ./dataset/football_true_community.groups ./dataset/football_detected_community.groups
  $ ./pcomet -n 4 -i ./dataset/football_network.pairs
./dataset/football_detected_community.groups


Extrinsic or intrinsic measures are evaluated. For the extrinsic measures, two
input clusterings (collections of clusters/communities) are compared to each
other, whether one of them typically is a ground-truth clustering. For the
intrinsic measures, the clustering is processed together with the respective
input network (graph).


  -h, --help              Print help and exit
  -V, --version           Print version and exit
  -n, --num=SHORT         the number of threads to be used.  (default=`1')
  -f, --cpufreq=SHORT     CPU frequency to measure timing of the metrics, MHz
                            (can be fetched by `$ lscpu`).  (default=`2100')

 Group: gr_metrics
  Quality metrics type to be evaluated
  -e, --extrinsic[=ENUM]  extrinsic quality metrics to be evaluated  (possible
                            values="all", "f1m", "nvd" default=`all')
  -i, --intrinsic[=ENUM]  intrinsic quality metrics to be evaluated  (possible
                            values="all" default=`all')
  -w, --weighted          the input network is weighted  (default=off)
  -d, --directed          the input network is directed  (default=off)
  ```
> The `MPI-based` implementation has another (original) execution parameters and output format.
> 
> **Parameters** for calculating the metrics with ground truth community structure:
> `$ mpirun -np 4 ./mpimetric metricType realCommunityFile detectedCommunityFile`  
> **Parameters** for calculating the metrics with ground truth community structure:
> `mpirun -np 4 ./mpimetric metricType detectedCommunityFile networkFile [isUnweighted] [isUndirected]`  
> Parameters introduction:  
> `metricType`: metricType=1 for metrics with ground truth community structure; metricType=0 for metrics without ground truth community structure.  
> `realCommunityFile`: it is the file of the ground truth community structure.  
> `detectedCommunityFile`: it is the file of the discovered community structure.  
> `networkFile`: the file of the network.  
> `isUnweighted`: it is optional and default value is 1; isUnweighted=1 for unweighted nework; isUnweighted=0 for weighted network.  
> `isUndirected`: it is optional and default value is 1; isUndirected=1 for undirected network; isUndirected=0 for directed network.  
> `numThreads`: the number of threads adopted in the parallel Pthreads program; Its value should be equal to or larger than 1.
>  
> **Output format** of `parallel MPI programs` for calculating the metrics *with ground truth* community structure:
> `numProcs total_running_time_information_theory_metrics computation_time msg_passing_time total_running_time_cluster_matching_metrics computation_time msg_passing_time total_running_time_pair_counting_metrics computation_time msg_passing_time
numProcs VI NMI F-measure NVD RI ARI JI`  
> Output format of `parallel MPI programs` for calculating the metrics *without ground truth* community structure:
> `numProcs total_running_time 
numProcs modularity modularity_density #intra-edges intra-density contraction #inter-edges expansion conductance`

## Compilation
Just `$ make` for the `Pthread`-based implementation or perform the custom compilation for the MPI-based implementation: `$ mpic++ [OPTIONS] src/MPIMetricMain.cpp -o mpcomet`.

## Related Projects
- [xmeasures](https://github.com/eXascaleInfolab/xmeasures)  - Extrinsic quality (accuracy) measures evaluation for the overlapping clustering on large datasets: family of mean F1-Score (including clusters labeling), Omega Index (fuzzy version of the Adjusted Rand Index) and standard NMI (for non-overlapping clusters).
- [GenConvNMI](https://github.com/eXascaleInfolab/GenConvNMI) - Overlapping NMI evaluation that is compatible with the original NMI and suitable for both overlapping and multi resolution (hierarchical) clustering evaluation.
- [OvpNMI](https://github.com/eXascaleInfolab/OvpNMI) - Another method of the NMI evaluation for the overlapping clusters (communities) that is not compatible with the standard NMI value unlike GenConvNMI, but it is much faster than GenConvNMI.
- [Clubmark](https://github.com/eXascaleInfolab/clubmark) - A parallel isolation framework for benchmarking and profiling clustering (community detection) algorithms considering overlaps (covers).
- [CluSim](https://github.com/Hoosier-Clusters/clusim) - A Python module that evaluates various extrinsic quality metrics (accuracy) for non-overlapping (single membership) clusterings.
- [resmerge](https://github.com/eXascaleInfolab/resmerge)  - Resolution levels clustering merger with filtering. Flattens hierarchy/list of multiple resolutions levels (clusterings) into the single flat clustering with clusters on various resolution levels synchronizing the node base.
- [ExecTime](https://bitbucket.org/lumais/exectime/)  - A lightweight resource consumption profiler.
