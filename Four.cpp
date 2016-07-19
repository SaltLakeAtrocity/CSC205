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

bool openfiles(ifstream & salesf, ifstream & productf, ofstream & outfile, ofstream & errorfile);

void readprod(ifstream & productf, productType productdata[], int & prodcount);
void readsales(ifstream & salesf, ofstream & errorfile, salesType salesdata[], productType productdata[], int & salescount, int prodcount);

float bonuscalc(salesType salesdata[], productType productdata[], int salescount, int prodcount);
void outputdata(ofstream & outfile, salesType salesdata[], productType productdata[], int salescount, int prodcount);

void closefiles(ifstream & salesf, ifstream & productf, ofstream & outfile, ofstream & errorfile);

int main() {
	ifstream salesf;
	ifstream productf;
	ofstream outfile;
	ofstream errorfile;
	salesType salesdata[30];
	productType productdata[50];
	int salescount=0;
	int prodcount=0;
	
    if	(! openfiles(salesf, productf, outfile, errorfile)) { cout << "Error opening file.  Closing program.\n"; return 1; }

	readprod(productf, productdata, prodcount);
	readsales(salesf, errorfile, salesdata, productdata, salescount, prodcount);
    
	outputdata(outfile, salesdata, productdata, salescount, prodcount);
	closefiles(salesf, productf, outfile, errorfile);
	return 0;
}
//************************************************************************************
bool openfiles(ifstream & salesf, ifstream & productf, ofstream & outfile, ofstream & errorfile) {
	//string salesname, productname, outputname;
	//cout << "Please tell me your sales file name.\n";
	//cin >> salesname;
	//salesf.open(salesname.c_str());
	//cout << "Please tell me your product file name.\n";
	//cin >> productname;
	//productf.open(productname.c_str());
	//cout << "Please name your outfile file.\n";
	//cin >> outputname;
	//outfile.open(outputname.c_str());
	productf.open("products.txt");
	salesf.open("salesFile.txt");
	outfile.open("Outputfile.txt");
	errorfile.open("Errorfile.txt");
    if (! productf.is_open()) {
        return false;
    }
	if (! salesf.is_open()) {
		return false;
	}
	if (! outfile.is_open()) {
		return false;
	}
	if (! errorfile.is_open()) {
		return false;
	}
    return true;
}
//************************************************************************************
//************************************************************************************
void readprod(ifstream & productf, productType productdata[], int & prodcount) {
    while (productf) {
        productf >> productdata[prodcount].productnum >> productdata[prodcount].price;
        prodcount++;
    }
}
//************************************************************************************
void readsales(ifstream & salesf, ofstream & errorfile, salesType salesdata[], productType productdata[], int & salescount, int prodcount) {
	int i = 0;
	int found = 0;
	int productnum;
	int qty;
	
	while (salesf) {
        salesf 	>> 	salesdata[salescount].firstname >> salesdata[salescount].lastname >> salesdata[salescount].id >> productnum;

		while (productnum != -1) {
            salesf	>>	qty;

            for (i = 0; i < prodcount; i++) {
				if (productnum==productdata[i].productnum) {
					salesdata[salescount].totalsales += (qty * productdata[i].price);
					found = 1;
				}
	    	}
	    	if (found!=1) {
				errorfile	<<	"Error Product #: " << productnum << "\n";
				}
            salesf  >>  productnum;
		}
		salescount++;
    }
}
//************************************************************************************
//************************************************************************************
float bonuscalc(salesType salesdata[], productType productdata[], int salescount, int prodcount) {
	int i = 0;
	for (i = 0; i < salescount; i++) {
    	if (salesdata[i].totalsales <= 500.00) {
			salesdata[i].bonus = 0.00;
		}
		if (salesdata[i].totalsales <= 1000.00 && salesdata[i].totalsales >= 500.01) {
			salesdata[i].bonus = 500.00;
		}
		if (salesdata[i].totalsales <= 5000.00 && salesdata[i].totalsales >= 1000.01) {
			salesdata[i].bonus = 1000.00;
		}
		if (salesdata[i].totalsales >= 5000.01) {
			salesdata[i].bonus = 2000.00;
		}
	}
	return salesdata[i].bonus;
}
//************************************************************************************
void outputdata(ofstream & outfile, salesType salesdata[], productType productdata[], int salescount, int prodcount) {
	cout 	<< setw(14) << left << "First Name" << setw(14) << left << "Last Name" 	<< setw(8) << left << "ID"
			<< setw(14) << left << "Total Sales"<< setw(14) << left << "Bonus"		<< endl;
	cout	<< left		<< "=============================================================================\n";
	outfile << setw(14) << left << "First Name" << setw(14) << left << "Last Name" 	<< setw(8) << left << "ID"
			<< setw(14) << left << "Total Sales"<< setw(14) << left << "Bonus"		<< endl;
	outfile	<< left		<< "=============================================================================\n";
	int i=0;
	for (i = 0; i < salescount; i++) {
		cout	<<	fixed 	<< showpoint 	<< setprecision(2);
		cout	<<	setw(12)<< left			<< salesdata[i].firstname << " "
				<<	setw(12)<< left			<< salesdata[i].lastname << " "
				<<	setw(6)	<< left			<< salesdata[i].id << " "
				<<	setw(12)<< left			<< "$"	<<	salesdata[i].totalsales << " "
				<<	setw(12)<< left			<< "$"	<< salesdata[i].bonus << "\n";
		outfile	<<	fixed 	<< showpoint 	<< setprecision(2);
		outfile	<<	setw(12)<< left			<< salesdata[i].firstname << " "
				<<	setw(12)<< left			<< salesdata[i].lastname << " "
				<<	setw(6)	<< left			<< salesdata[i].id << " "
				<<	setw(12)<< left			<< "$"	<<	salesdata[i].totalsales << " "
				<<	setw(12)<< left			<< "$"	<< salesdata[i].bonus << "\n";
	}
}
//************************************************************************************
//************************************************************************************
void closefiles(ifstream & salesf, ifstream & productf, ofstream & outfile, ofstream & errorfile) {
    productf.close();
	salesf.close();
	outfile.close();
	errorfile.close();
}
