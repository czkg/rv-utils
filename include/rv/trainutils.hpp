#ifndef DEEPC_TRAINUTILS_H
#define DEEPC_TRAINUTILS_H

#include <vector>
#include <iostream>


namespace rv {

template <typename T>
void crossValidationSet(const std::vector<T>& set, int cv, std::vector<std::vector<T> >& trainsets, std::vector<std::vector<T> >& testsets) {
    int nPartitionSamples = set.size() / cv;
    std::cout << nPartitionSamples << " * " << cv << std::endl;

    for(int cvIdx = 0; cvIdx < cv; ++cvIdx) {
        std::vector<T> trainset;
        std::vector<T> testset;

        int testsetFrom = cvIdx * nPartitionSamples;
        int testsetTo = cvIdx == (cv - 1) ? set.size() : (cvIdx + 1) * nPartitionSamples;

        for(int sampleIdx = 0; sampleIdx < set.size(); ++sampleIdx) {
            T sample = set.at(sampleIdx);

            if(sampleIdx >= testsetFrom && sampleIdx < testsetTo) {
                testset.push_back(sample);
            }
            else {
                trainset.push_back(sample);
            }
        }

        trainsets.push_back(trainset);
        testsets.push_back(testset);
    }
}


} //namespace deepc

#endif // TRAINUTILS_H
