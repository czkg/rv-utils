// Copyright (C) 2015 Institute for Computer Graphics and Vision (ICG),
//   Graz University of Technology (TU GRAZ)

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the ICG, TU GRAZ.
// 4. Neither the name of the ICG, TU GRAZ nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY ICG, TU GRAZ ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL ICG, TU GRAZ BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
