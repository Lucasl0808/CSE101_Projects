#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

int main(void){
        Dictionary A;
        std::string S[] = {"ay", "cee", "bee", "e", "dee"};
        for(int i = 0; i < 5; i++){
                A.setValue(S[i], i+1);
        }
        std::cout << A << std::endl;
        A.remove("cee");
        std::cout << A << std::endl;

        std::cout << A.size() << std::endl;
        A.begin();
        std::cout << A.currentKey() << std::endl;
        A.next();
        std::cout << A.currentKey() << std::endl;
        A.end();
        std::cout << A.currentKey() << std::endl;
        A.prev();
        std::cout << A.currentKey() << std::endl;
        A.prev();
        A.prev();
        std::cout << A.currentKey() << std::endl;
        Dictionary B = A;
        std::cout << B << std::endl;
        B.setValue("LOL", 6);
        if(A == B){
                std::cout << "A = B" << std::endl;
        }
	std::string P[] = {"plaices",
                     "ambusher",
                     "crosby",
                     "wattles",
                     "pardoner",
                     "pythons",
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                     "dissocialised",
                     "cohabit",
                     "hemiolia",
                     "cantling",
                     "glamorized",
                     "millesimal",
                     "glagolitic"};
	Dictionary C;
	for(int i = 0; i < 26; i ++){
		C.setValue(P[i], i +1);
		std::cout << C << std::endl;
	}
	std::cout << C.size() << std::endl;
	std::cout << C << std::endl;
	
	std::string O[] = {"second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",      
                  };

	for(int i = 0; i < 13; i ++){
		C.remove(O[i]);
	}
	std::cout << C << std::endl;
}


