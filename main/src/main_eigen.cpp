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
		std::cout << "Usage : ./eigenface training.csv test.csv" << std::endl;
		return (-1);
	}

	DbInteractions			DBI("42cv");
	SessionEig				sessionEig(argv[1]);
	cv42::Eigenface			eigenface;

	try {
		eigenface.train(sessionEig);
		DBI.store(sessionEig);

		SessionTest			sessionTest(argv[2], &sessionEig);

		eigenface.predict(sessionTest);
		DBI.store(sessionTest);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Error" << std::endl;
	}

	return (0);
}
