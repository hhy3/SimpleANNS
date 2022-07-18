# SimpleANNS

Naive implementations of some ANN (Approximate Nearest Neighbor) search algorithms without any optimization and generalization.

## Progess 
- [x] [FLAT](https://github.com/hhy3/SimpleANNS/blob/master/src/FlatIndex.hpp)
- [x] [IVF_FLAT](https://github.com/hhy3/SimpleANNS/blob/master/src/IVFFlatIndex.hpp)
- [ ] IVF_SQ8
- [ ] IVF_PQ
- [ ] HNSW
- [ ] RHNSW_FLAT
- [ ] RHNSW_SQ
- [ ] RHNSW_PQ

## Algorithms

The algorithms used in ANN search can generally be classified as **tree based**, **LHS based**, **graph based** and **IVF based**, where graph and IVF based algorithms are more popular today but tree and LHS based algorithms are no longer commonly used. Moreover, **quantization** can be used to compress data and reduce memory usage.

**[CVPR20 Tutorial] Billion-scale Approximate Nearest Neighbor Search](https://www.youtube.com/watch?v=SKrHs03i08Q)** is a good tutorial for ANN beginners.

**[ann-benchmarks](https://github.com/erikbern/ann-benchmarks/)** contains some tools to benchmark various implementations of approximate nearest neighbor (ANN) search for different metrics.
### Tree Based
Based on the idea of partitioning vector space, performs poorly in high demensional vector space due to the curse of dimensionality.

- **[FLANN](https://github.com/flann-lib/flann)** automatically select "Randomized KD Tree" or "k-means Tree"
  - paper: [AST APPROXIMATE NEAREST NEIGHBORS WITH AUTOMATIC ALGORITHM CONFIGURATION](https://lear.inrialpes.fr/~douze/enseignement/2014-2015/presentation_papers/muja_flann.pdf) 
    - take any given dataset and desired degree of precision and use these to automatically determine the best algorithm and parameter values.

**- [Annoy](https://github.com/spotify/annoy)** is based on random projection forest, uses multi-tree with a shared priority queue
  - Blog: [Nearest neighbors and vector models – part 2 – algorithms and data structures](https://erikbern.com/2015/10/01/nearest-neighbors-and-vector-models-part-2-how-to-search-in-high-dimensional-spaces.html)

### LHS (Locality Sensitive Hashing) Based
Instead of collision avoidance, the general idea of hashing, the idea of LSH is to expolit collisions for mapping points which are nearby into the same bucket.
It is popular in theory area, but performs poorly in practice with real-world data.

- **[FALCONN](https://github.com/FALCONN-LIB/FALCONN)**


### Graph Based

Popular in recent years, mostly based on the idea of proximity graph. Given a query, start from a source point (randomly chosen or supplied by a separate algorithm), greedily find the closest point to the query.

Blog: [Proximity Graph-based Approximate Nearest Neighbor Search](https://zilliz.com/learn/pg-based-anns)

- **NSW** has small world nagigation properties which has **polylog** time complexity of insertion and seraching.
  - Paper: [Approximate nearest neighbor algorithm based on navigable small world graphs](https://publications.hse.ru/pubs/share/folder/x5p6h7thif/128296059.pdf)

- **[HNSW](https://github.com/nmslib/hnswlib)** incrementally builds a multi-layer structure consisting from hierarchical set of proximity graphs (layers) for nested subsets of the stored elements, can be seen as an extension of the probabilistic skip list structure with proximity graphs instead of the linked lists
  - Paper: [Efficient and robust approximate nearest neighbor search using Hierarchical Navigable Small World graphs](https://arxiv.org/ftp/arxiv/papers/1603/1603.09320.pdf)

- **[NSG](https://github.com/ZJULearning/nsg)**
  - Paper: [Fast Approximate Nearest Neighbor Search With The Navigating Spreading-out Graph](https://arxiv.org/pdf/1707.00143.pdf)

- **[Vamana (DiskANN)](https://github.com/microsoft/DiskANN)** optimizes for disk IO, and makes previous NSG method SSD-friendly.
  - Paper: [DiskANN: Fast Accurate Billion-point Nearest Neighbor Search on a Single Node](https://suhasjs.github.io/files/diskann_neurips19.pdf)
  - Blog: [DiskANN: A Disk-based ANNS Solution with High Recall and High QPS on Billion-scale Dataset](https://zilliz.com/blog/diskann-a-disk-based-anns-solution-with-high-recall-and-high-qps-on-billion-scale-dataset)

- **[SPTAG](https://github.com/microsoft/SPTAG)**
  - Paper: [Query-driven iterated neighborhood graph search for large scale indexing](https://jingdongwang2017.github.io/Pubs/ACMMM12-GraphSearch.pdf)

- **[NGT](https://github.com/yahoojapan/NGT)** is based on navgating spread-out graph and is being used in Taobao now.
  - Paper: [Optimization of Indexing Based on k-Nearest Neighbor Graph for Proximity](https://arxiv.org/pdf/1810.07355.pdf)

### Inverted Index Based
This algorithm clusters the dataset to partition the space to [Voronoi Cells](https://oi-wiki.org/geometry/triangulation/#voronoi), and by searching only neighbor cells reduces the data points needed to search.

- **[IVF-HNSW](https://github.com/dbaranchuk/ivf-hnsw)**
  - Paper: [Revisiting the Inverted Indices for Billion-Scale Approximate Nearest Neighbors](https://openaccess.thecvf.com/content_ECCV_2018/papers/Dmitry_Baranchuk_Revisiting_the_Inverted_ECCV_2018_paper.pdf)


### Quantization
- **[PQ](https://github.com/matsui528/nanopq/blob/main/nanopq/pq.py)** Split a vector into subspaces, and quantize each sub-vector.
  - [Faiss](https://github.com/facebookresearch/faiss) is based on PQ + IVF.
  - Paper: [Product Quantization for Nearest Neighbor Search](https://hal.inria.fr/inria-00514462v2/document)
  - Survey: [A Survey of Product Quantization](https://www.jstage.jst.go.jp/article/mta/6/1/6_2/_pdf)

- **[ScaNN](https://github.com/google-research/google-research/tree/master/scann)**
  - Paper: [Accelerating Large-Scale Inference with Anisotropic Vector Quantization](http://proceedings.mlr.press/v119/guo20h/guo20h.pdf)

## Datasets

- **[SIFT](http://corpus-texmex.irisa.fr/)**
