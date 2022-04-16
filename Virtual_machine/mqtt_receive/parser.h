using namespace std;
#include <jsoncpp/json/json.h>




int parse(std::string json_in, int &n1, int &n2)
{

	std::string parse_out;
	int number;
	Json::Reader  reader; //reader object
	Json::Value   obj;   //Name value par > value object
	printf ("\n String ot parse = %s \n",json_in.c_str());

	if(reader.parse(json_in, obj)==true)
	{
		if (obj["LID"].isString())
		{
			parse_out=obj["LID"].asString();
			printf("\n MyCommand = %s \n",parse_out.c_str());
			number=atoi(parse_out.c_str());
			n1=number;
		};

		if (obj["LID"].isInt())
		{
			n1=obj["LID"].asInt();
			
			/*
			switch (number){
			case 1:{
				return 1;
			}
			case 2:{
				return 2;
			}
			case 3:{
				return 3;
			}
			case 4:{
				return 4;
			}
			default:{
				printf("Wrong value (select 1-4)\n");break;
			}

			};
			*/

		}

		if (obj["COM"].isInt())
                {
                        n2=obj["COM"].asInt();
		}


	}else
	{
		printf("\n --- Error in JSON parsing ---- \n");
	};

	return number;
}
