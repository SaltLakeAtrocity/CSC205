//
// Robert VanCleave
// Programming Assignment Four
// Uses float, int, and void return type functions
// Program requires .txt file header input parameters as a prerequisite
// Program utilizes structures, arrays, and functions
// 		to calculate and output sales data.
//

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include "salestype.h"
#include "productlog.h"
using namespace std;

bool opensales(ifstream & salesf, ofstream & outfile);
void readsales(ifstream & salesf, salesType salesdata[], productType productdata[], int salescount, int prodcount);
bool openprod(ifstream & productf);
void readprod(ifstream & productf, productType productdata[], int prodcount);
float salescalc(salesType salesdata[], productType productdata[], int salescount, int prodcount);
void outputdata(ifstream & salesf, ifstream & productf, ofstream & outfile, salesType salesdata[], productType productdata[],
				int salescount, int prodcount);

int main() {
	ifstream salesf, productf;
	ofstream outfile;
	salesType salesdata[30];
	productType productdata[50];
	int salescount=0, prodcount=0;
	
if	(! openprod(productf)) {
	cout << "Error opening file.  Closing program.\n";
	return 1;
}
	readprod(productf, productdata, prodcount);
if (! opensales(salesf, outfile)) {
	cout << "Error opening file.  Closing program.\n";
	return 1;
}
	readsales(salesf, salesdata, productdata, salescount, prodcount);
	salesdata[salescount].totalsales = salescalc(salesdata, productdata, salescount, prodcount);
	outputdata(salesf, productf, outfile, salesdata, productdata, salescount, prodcount);
	return 0;
}
//************************************************************************************
bool opensales(ifstream & salesf, ofstream & outfile) {
    salesf.open("salesFile.txt");
	outfile.open("Outputfile.txt");
	if (! salesf.is_open()) {
		return false;
	}
	if (! outfile.is_open()) {
		return false;
	}
	cout << "File opened successfully.\n";
	return true;
}
//************************************************************************************
void readsales(ifstream & salesf, salesType salesdata[], productType productdata[], int salescount, int prodcount) {
	int i, salesnum;
	while (salesf) {
		salesf 	>> 	salesdata[salescount].firstname >> salesdata[salescount].lastname >> salesdata[salescount].id;
		while (salesnum != -1) {
			salesf	>>	salesnum >> salesdata[salescount].numsales;
			for (i = 0, i < productdata[i].productnum, i++) {
				if (salesnum==productdata[i].productnum) {
					
				}
			}
		}
	}
		salescount++;
}
//************************************************************************************
bool openprod(ifstream & productf) {
    productf.open("products.txt");
	if (! productf.is_open()) {
		return false;
	}
	return true;
}
//************************************************************************************
void readprod(ifstream & productf, productType productdata[], int prodcount) {
		productf >> productdata[prodcount].productnum >> productdata[prodcount].price;
	while (productf) {
		productf >> productdata[prodcount].productnum >> productdata[prodcount].price;
		prodcount++;
	}
}
//************************************************************************************
float salescalc(salesType salesdata[], productType productdata[], int salescount, int prodcount) {
	//salesdata[salescount].totalsales
}
//************************************************************************************
void outputdata(ifstream & salesf, ifstream & productf, ofstream & outfile, salesType salesdata[], productType productdata[],
				int salescount, int prodcount) {
		
}
//************************************************************************************
