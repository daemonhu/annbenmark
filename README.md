simple test for ann, benchmark is not completed

Build steps:
1. download newest dependencies...(skip this works, if not, orginal nsg source code should be modified)
2. download sift dataset, siftsmall dataset already included in this repo for testing
3. run mkdir build && cmake ../
4. example for testing...
./test_ann ../dataset/siftsmall/siftsmall_base.fvecs ../dataset/siftsmall/siftsmall_query.fvecs ../dataset/siftsmall/siftsmall_groundtruth.ivecs 5 6000 1000
