#include<iostream>
#include<filesystem>
#include<string>
#include<fstream>
#define KILOBYTE 1024
#define MEGABYTE (KILOBYTE*KILOBYTE)
#define GIGABYTE (MEGABYTE*KILOBYTE)
using std::ofstream;
using std::ifstream;
namespace fs =  std::filesystem;


/*#include <iostream>
	#include <filesystem>

	namespace fs = std::filesystem;

	int main() {
	    // Check if a file or directory exists
	    if (fs::exists("my_directory")) {
	        std::cout << "my_directory exists." << std::endl;
	    }
	
	    // Create a directory
	    fs::create_directory("my_directory");

	    // List the contents of a directory
	    for (const auto& entry : fs::directory_iterator("my_directory")) {
	        std::cout << entry.path() << std::endl;
	    }

	    // Rename a file or directory
	    fs::rename("my_directory", "new_directory");

	    // Remove a file or directory
	    fs::remove_all("new_directory");

	    return 0;
	}*/



int main()
{

	//list a directory and get a size of each file :
	bool active = true;

	std::vector<std::string> commands = {"list","create dir","create file","delete file","delete dir","erase dir","erase file"};


	std::string help = "-help";
	std::string command;
	std::string dirPath;
	std::string dirName;
	std::string dir;
	fs::path dirpath;
	std::string fileName;
	
	while(active)
	{
		std::cout<<"@~> ";
		std::getline(std::cin,command);
		if(command=="-help")
		{	
			std::cout<<"\t\t>>Commands<<\n";
			for(const auto &it: commands)
				std::cout<<"\t"<<it<<"\n";
		}
		if(command == "quit"){std::cout<<"\n~ABORTED~\n";break;}

		if(command == "list")
		{
			std::cout<<"DirPath: ";
			std::cin>>dirPath;
			if(dirPath == "quit"){std::cout<<"\n~ABORTED~\n";break;}
			//std::string dirPath  = "C:\\Users\\kakap\\OneDrive\\Documents\\there";
			if(fs::exists(dirPath) && fs::is_directory(dirPath))
			{
				std::cout<<"\nDIR("<<dirPath<<")'S LIST OF FILES:\n";
				for(const auto& it : fs::directory_iterator(dirPath))
				{
					if(fs::exists(it.path()))
					{
						if(fs::is_directory(it.path()))
							std::cout<<"~DIR~\n\n";
						else
						{
							std::uintmax_t fileSize = fs::file_size(it.path());
							double eventualSize;
							std::string file_info;
							if(fileSize>=KILOBYTE && fileSize<= MEGABYTE)
							{
								eventualSize = static_cast<double>(fileSize)/KILOBYTE;
								file_info = "NAME:  "+it.path().string()+"  SIZE:  "+std::to_string(eventualSize)+" KB\n";
							}
							else if(fileSize>=MEGABYTE && fileSize<=GIGABYTE)
							{
								eventualSize = static_cast<double>(fileSize)/MEGABYTE;
								file_info = "NAME:  "+it.path().string()+"  SIZE:  "+std::to_string(eventualSize)+" MB\n";
							}
							else if(fileSize>=GIGABYTE)
							{
								eventualSize = static_cast<double>(fileSize)/GIGABYTE;
								file_info = "NAME:  "+it.path().string()+"  SIZE:  "+std::to_string(eventualSize)+" GB\n";
							}
							else
								file_info = "NAME:  "+it.path().string()+"  SIZE:  "+std::to_string(fileSize)+" B\n";
							
							//std::string file_info = "NAME:  "+it.path().string()+"  SIZE:  "+std::to_string(fileSize)+'\n';
							size_t position = file_info.find(dirPath);
							if(position != std::string::npos)
							{
								file_info.replace(position,dirPath.size(),""); //replace the path with ""
							}
							std::cout<<file_info<<"\n";
						}
					}
				}
			}
		}

		if(command == "create dir")
		{
			std::cout<<"\nDirectory Path : ";
			std::cin>>dirPath;
			std::cout<<"\nDirectory Name: ";
			std::cin>>dirName;
			fs::path dir = dirPath; 
			dir/=dirName; 
			if(!fs::exists(dir)) //check if the dir already exists
			{
				if(fs::create_directory(dir))
					std::cout<<dirName<<" is created successfully\n";
				else
					std::cerr<<"Failed to create "<<dirName<<'\n';
			}
			else
				std::cout<<"The Directory is already exists\n";
			


		}
		if(command =="create file")
		{
			std::cout<<"DirPath: ";
			std::cin>>dirPath;
			dirpath=dirPath;
			std::cout<<"FileName: ";
			std::cin>>fileName;

			fs::path FileName = dirpath / fileName;
			if(fs::exists(dirPath))
			{
				ofstream outFile(FileName.string());
				if(outFile.is_open())
				{
					outFile<<"New File\n";
					outFile.close();
				}
				else
					std::cerr<<"File couldn't be created\n";

			}

		}

		
	}

	return 0;
}