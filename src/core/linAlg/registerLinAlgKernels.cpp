#include <compileKernels.hpp>
#include <tuple>

void registerLinAlgKernels()
{
  occa::properties kernelInfo = platform->kernelInfo;

  const std::string oklDir = getenv("NEKRS_KERNEL_DIR") + std::string("/core/linAlg/");
  const bool serial = platform->serial;

  const std::string extension = serial ? ".c" : ".okl";
  const std::vector<std::pair<std::string, bool>> allKernels{
      {"fill", false},
      {"pfill", false},
      {"vabs", false},
      {"add", false},
      {"scale", false},
      {"scaleMany", false},
      {"axpby", true},
      {"paxpby", true},
      {"axpbyMany", true},
      {"paxpbyMany", true},
      {"axpbyz", false},
      {"axpbyzMany", false},
      {"axmy", true},
      {"paxmy", false},
      {"axmyMany", true},
      {"axmyVector", true},
      {"axmyz", false},
      {"paxmyz", true},
      {"axmyzMany", false},
      {"paxmyzMany", false},
      {"ady", false},
      {"adyz", false},
      {"adyMany", false},
      {"padyMany", false},
      {"axdy", false},
      {"aydx", false},
      {"aydxMany", false},
      {"axdyz", false},
      {"sum", false},
      {"sumMany", false},
      {"min", false},
      {"max", false},
      {"amax", false},
      {"amaxMany", false},
      {"norm2", true},
      {"norm2Many", true},
      {"norm1", true},
      {"norm1Many", true},
      {"weightedNorm1", true},
      {"weightedNorm1Many", true},
      {"weightedNorm2", true},
      {"weightedNorm2Many", true},
      {"weightedSqrSum", true},
      {"innerProd", true},
      {"weightedInnerProd", true},
      {"weightedInnerProdMany", true},
      {"weightedInnerProdMulti", false},
      {"weightedInnerProdMultiDevice", false},
      {"crossProduct", false},
      {"unitVector", false},
      {"entrywiseMag", false},
      {"linearCombination", false},
      {"relativeError", false},
      {"absoluteError", false},
      {"magSqrVector", false},
      {"magSqrSymTensor", false},
      {"magSqrSymTensorDiag", false},
      {"magSqrTensor", false},
      {"mask", false},
      {"pmask", false},
  };

  std::string kernelName;
  bool nativeSerialImplementation;
  for (auto &&nameAndSerialImpl : allKernels) {
    std::tie(kernelName, nativeSerialImplementation) = nameAndSerialImpl;
    const std::string extension = (serial && nativeSerialImplementation) ? ".c" : ".okl";
    const bool pfloatKernel = (kernelName.front() == 'p') ? true : false;
    const std::string prefix = ""; // "linAlg::"

    if (pfloatKernel && (sizeof(dfloat) == sizeof(pfloat))) continue; 

    std::string fileName = kernelName;
    occa::properties props = kernelInfo;
    if (pfloatKernel) {
      props["defines/dfloat"] = pfloatString;
      fileName.erase(0, 1);
    }

    platform->kernelRequests.add(prefix + kernelName, oklDir + fileName + extension, props);
  }
}
