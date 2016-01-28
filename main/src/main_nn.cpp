#include <dbInteractions.hpp>
#include <SessionEig.hpp>
#include <Eigenface.hpp>
#include <NN.hpp>
#include <iostream>
#include <exception>

int							main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage : ./nn training.csv test.csv" << std::endl;
		return (-1);
	}

	DbInteractions			DBI("42cv");
	cv42::NN			nn(argv[1], 100, 1, 0);

	try {
		nn.train();
		DBI.store(nn);

		SessionTest			sessionTest(argv[2], &nn);

		nn.predict(sessionTest);
		DBI.store(sessionTest);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Error" << std::endl;
	}

	return (0);
}
