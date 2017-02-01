// CLP includes
#include "paramap2itkimageCLP.h"

// DCMQI includes
#undef HAVE_SSTREAM // Avoid redefinition warning
#include "dcmqi/ParaMapConverter.h"


int main(int argc, char *argv[])
{
  PARSE_ARGS;

  DcmFileFormat sliceFF;
  std::cout << "Opening input file " << inputFileName.c_str() << std::endl;
  CHECK_COND(sliceFF.loadFile(inputFileName.c_str()));
  DcmDataset* dataset = sliceFF.getDataset();

  pair <FloatImageType::Pointer, string> result =  dcmqi::ParaMapConverter::paramap2itkimage(dataset);

  string fileExtension = dcmqi::Helper::getFileExtensionFromType(outputType);

  typedef itk::ImageFileWriter<FloatImageType> WriterType;
  WriterType::Pointer writer = WriterType::New();
  stringstream imageFileNameSStream;
  imageFileNameSStream << outputDirName << "/" << "pmap" << fileExtension;
  writer->SetFileName(imageFileNameSStream.str().c_str());
  writer->SetInput(result.first);
  writer->SetUseCompression(1);
  writer->Update();

  stringstream jsonOutput;
  jsonOutput << outputDirName << "/" << "meta.json";

  ofstream outputFile;
  outputFile.open(jsonOutput.str().c_str());
  outputFile << result.second;
  outputFile.close();

  return EXIT_SUCCESS;
}
