/*

   The MIT License (MIT)

   Copyright (c) 2017 Tim Warburton, Noel Chalmers, Jesse Chan, Ali Karakus

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

 */

#include "elliptic.h"
#include <string>
#include "platform.hpp"
#include "linAlg.hpp"

void ellipticBuildMultigridLevelKernels(elliptic_t *elliptic)
{
  auto mesh = elliptic->mesh;

  std::string prefix = "Hex3D";

  int M;
  platform->options.getArgs("POLYNOMIAL DEGREE", M);

  const std::string orderSuffix = std::string("_") + std::to_string(mesh->N);
  const std::string poissonPrefix = elliptic->poisson ? "poisson-" : "";

  std::string kernelName;

  kernelName = "updateChebyshev";
  elliptic->updateChebyshevKernel = platform->kernelRequests.load(kernelName + orderSuffix);

  kernelName = "updateFourthKindChebyshev";
  elliptic->updateFourthKindChebyshevKernel = platform->kernelRequests.load(kernelName + orderSuffix);

   kernelName = "ellipticBlockBuildDiagonalPfloatHex3D";
   elliptic->ellipticBlockBuildDiagonalPfloatKernel =
     platform->kernelRequests.load(poissonPrefix + kernelName + orderSuffix);
   elliptic->ellipticBlockBuildDiagonalKernel = nullptr; 
}
