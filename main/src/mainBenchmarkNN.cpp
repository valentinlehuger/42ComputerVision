#include <SessionEig.hpp>
#include <Eigenface.hpp>
#include <NN.hpp>
#include <iostream>
#include <vector>
#include <string>

float	getPct(SessionTest *st) {
  int				win = 0;
  std::vector<std::string>	expectLabels = *(st->getLabels());
  std::vector<std::string>	predictedLabels = st->getResultLabels();
  int				total = expectLabels.size();

  for (int i = 0; i < total; ++i) {
    if (expectLabels[i] == predictedLabels[i])
      ++win;
  }
  return (static_cast<float>(win) / static_cast<float>(total));
}

int							main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage : ./nn training.csv test.csv" << std::endl;
		return (-1);
	}
	static const int neuronarr[] = {10, 25, 50, 100};
	std::vector<int> numberOfNeuron(neuronarr, neuronarr + sizeof(neuronarr) / sizeof(neuronarr[0]));
	static const float alphaarr[] = {1, 2, 3, 4};
	std::vector<float> alpha(alphaarr, alphaarr + sizeof(alphaarr) / sizeof(alphaarr[0]));
	static const float lambdaarr[] = {0, 1, 2, 3};
	std::vector<float> lambda(lambdaarr, lambdaarr + sizeof(lambdaarr) / sizeof(lambdaarr[0]));
	cv42::NN				*nn;
	SessionTest			*sessionTest;
	float				pctSum = 0;
	int				nloop = 1;

	std::cout << "Number of neurons,alpha,lambda,pct" << std::endl;
	for (int stepneuron = 0; stepneuron < numberOfNeuron.size(); ++stepneuron) {
	  for (int stepalpha = 0; stepalpha < alpha.size(); ++stepalpha) {
	    for (int steplambda = 0; steplambda < lambda.size(); ++steplambda) {
	      pctSum = 0;
	      for (int i = 0; i < nloop; ++i) {
		nn = new cv42::NN(argv[1], numberOfNeuron[stepneuron], alpha[stepalpha], lambda[steplambda]);
		nn->train();
		sessionTest = new SessionTest(argv[2], nn);
		nn->predict(*sessionTest);
		pctSum += getPct(sessionTest);
		delete nn;
		delete sessionTest;
	      }
	      std::cout << numberOfNeuron[stepneuron] << "," << alpha[stepalpha] << "," << lambda[steplambda] << "," << pctSum / static_cast<float>(nloop) << std::endl;
	    }
	  }
	}
	return (0);
}

// g++ main/src/mainBenchmarkNN.cpp mongodb/srcs/csvReader.cpp  libimg/srcs/img_decompress.cpp   -I libcv/inc -I mongodb/inc  -I CImg-1.6.3/ -I libmath/inc/ -I libimg/inc/ -std=c++11 -O2 -lm -lpthread -pthread -Dcimg_display=0 -Dcimg_use_png -lpng
