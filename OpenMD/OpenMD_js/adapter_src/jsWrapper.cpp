// Embind of OpenMdRunner class
#include <emscripten/bind.h>
#include <adapters.h>

using namespace emscripten;
using namespace OpenMD;

// Binding code
EMSCRIPTEN_BINDINGS(OpenMdWrapper) {
  class_<OpenMdRunner>("OpenMdRunner")
    .constructor<>()
    .function("addIncludeData", &OpenMdRunner::addIncludeData)
    .function("removeIncludeData", &OpenMdRunner::removeIncludeData)
    .function("getOutputData", &OpenMdRunner::getOutputData)
	.function("getDumpData", &OpenMdRunner::getDumpData)
	.function("getEorData", &OpenMdRunner::getEorData)
	.function("getReportData", &OpenMdRunner::getReportData)
	.function("getStatData", &OpenMdRunner::getStatData)
	.function("runOmdJob", &OpenMdRunner::runOmdJob)
    ;
}

