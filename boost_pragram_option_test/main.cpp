#include <boost/program_options.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

namespace po = boost::program_options;
int helloworld(void )
{
	printf("helloworld\n");
	return 0;
}

int main(int argc, char *argv[])
{
	helloworld();
    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "produce help message")

        ("optimization,o",
         po::value<int>()->default_value(10),
         "Optimazation level")

        ("include-path,I",
         po::value< std::vector<std::string> >(),
         "include header")

        ("input-files",
         po::value< std::vector<std::string> >(),
         "input files");

    po::positional_options_description p;
    p.add("input-files", -1);

    po::variables_map vm;
    //po::store(po::parse_command_line(argc, argv, desc), vm);
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(),vm);
    po::notify(vm);

    if(vm.count("help"))
    {
        std::cout << desc  << std::endl;
        return 1;
    }

    if(vm.count("optimization"))
    {
        std::cout << "optimization is " << vm["optimization"].as<int>() << std::endl;
    }

    if (vm.count("include-path")) {
        auto incVec = vm["include-path"].as< std::vector<std::string> >();

        std::cout << "include paths are :\n";
        for (auto str : incVec) {
            std::cout << "\t" << str << std::endl;
        }
    }

    if (vm.count("input-files")) {
        auto inputVec = vm["input-files"].as< std::vector<std::string> >();

        std::cout << "input files are :\n";
        for (auto str : inputVec) {
            std::cout << "\t" << str << std::endl;
        }
    }

    return 0;
}
