# SimpleANNS

Naive implementations of some ANNS (Approximate Nearest Neighbor Search) algorithms without any optimization and generalization.

## Progess 
- [x] FLAT
- [ ] IVF_FLAT
- [ ] IVF_SQ8
- [ ] IVF_PQ
- [ ] HNSW
- [ ] RHNSW_FLAT
- [ ] RHNSW_SQ
- [ ] RHNSW_PQ

## Algorithms

### Tree Based
Based on the idea of partitioning vector space, performs poorly due to the curse of dimensionality.
- [Annoy](https://github.com/spotify/annoy)
  - Blog: [Nearest neighbors and vector models – part 2 – algorithms and data structures](https://erikbern.com/2015/10/01/nearest-neighbors-and-vector-models-part-2-how-to-search-in-high-dimensional-spaces.html)
### LHS (Locality Sensitive Hashing) Based
Popular in theory area, but performs poorly in practice with real-world data.

- [FALCONN](https://github.com/FALCONN-LIB/FALCONN)


### Graph Based

Popular in recent years, mostly based on the idea of [Navigable Small World Graph](https://en.wikipedia.org/wiki/Small-world_network). Given a query, start from a source point (randomly chosen or learned), greedily find the closest point to the query.

- [HNSW](https://github.com/nmslib/hnswlib) Just skip lists build on proximity graph.
  - Paper: [Efficient and robust approximate nearest neighbor search using Hierarchical Navigable Small World graphs](https://arxiv.org/ftp/arxiv/papers/1603/1603.09320.pdf)

- [NSG](https://github.com/ZJULearning/nsg)
  - Paper: [Fast Approximate Nearest Neighbor Search With The Navigating Spreading-out Graph](https://arxiv.org/pdf/1707.00143.pdf)

- [Vamana (DiskANN)](https://github.com/microsoft/DiskANN)
  - Paper: [DiskANN: Fast Accurate Billion-point Nearest Neighbor Search on a Single Node](https://suhasjs.github.io/files/diskann_neurips19.pdf)

- [SPTAG](https://github.com/microsoft/SPTAG)
  - Paper: [Query-driven iterated neighborhood graph search for large scale indexing](https://jingdongwang2017.github.io/Pubs/ACMMM12-GraphSearch.pdf)

- [NGT](https://github.com/yahoojapan/NGT)
  - Paper: [Optimization of Indexing Based on k-Nearest Neighbor Graph for Proximity](https://arxiv.org/pdf/1810.07355.pdf)

### Inverted Index Based
This algorithm clusters the dataset to partition the space to [Voronoi Cells](https://oi-wiki.org/geometry/triangulation/#voronoi), and by searching only neighbor cells reduces the data points needed to search.

- [IVF-HNSW](https://github.com/dbaranchuk/ivf-hnsw)
  - Paper: [Revisiting the Inverted Indices for Billion-Scale Approximate Nearest Neighbors](https://openaccess.thecvf.com/content_ECCV_2018/papers/Dmitry_Baranchuk_Revisiting_the_Inverted_ECCV_2018_paper.pdf)


### Quantization
- [PQ](https://github.com/matsui528/nanopq/blob/main/nanopq/pq.py) Split a vector into subspaces, and quantize each sub-vector.
  - [Faiss](https://github.com/facebookresearch/faiss)
  - Paper: [Product Quantization for Nearest Neighbor Search](https://hal.inria.fr/inria-00514462v2/document)
  - Survey: [A Survey of Product Quantization](https://www.jstage.jst.go.jp/article/mta/6/1/6_2/_pdf)

- [ScaNN](https://github.com/google-research/google-research/tree/master/scann)
  - Paper: [Accelerating Large-Scale Inference with Anisotropic Vector Quantization](http://proceedings.mlr.press/v119/guo20h/guo20h.pdf)

## Datasets

- [SIFT](http://corpus-texmex.irisa.fr/)
