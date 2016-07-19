//
// Robert VanCleave
// Programming Assignment Four
// Utilizes file data, .h healer files, and functions to output sales data
// Function signature listed under each initial function declaration
//

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include "salestype.h"
#include "productlog.h"
using namespace std;

bool openfiles(ifstream & salesf, ifstream & productf, ofstream & outfile, ofstream & errorfile);
	//openfiles() calls ifstream and ofstream values to open both input and output files
	//return type: bool (true/false)
	//pre: fstream variable declaration, a positive file open result
	//post: yields a bool output value that determines whether or not the rest of the program will carry on

void readprod(ifstream & productf, productType productdata[], int & prodcount);
	//readprod() calls the input product file data and assigns a variable to each value passed
	//return type: n/a (void function)
	//pre: requires successful ifstream procedure
	//post: passes values for product structure
void readsales(ifstream & salesf, ofstream & errorfile, salesType salesdata[], productType productdata[], int & salescount, int prodcount);
	//readsales() calls the input sales file data and assigns a variable to each value passed
	//return type: n/a (void function)
	//pre: requires successful ifstream procedure
	//post: passes values for sales structure; also passes errorfile into the ofstream

void bonuscalc(salesType salesdata[], productType productdata[], int salescount, int prodcount);
	//bonuscalc() uses sales structure data passed from readsales() to calculate the sales bonus
	//return type: n/a (void function)
	//pre: requires successful calculation of salesdata[].totalsales
	//post: passes a value for salesdata[].bonus
void outputdata(ofstream & outfile, salesType salesdata[], productType productdata[], int salescount, int prodcount);
	//outputdata() uses all the calculated data to output everything in an organized format
	//return type: n/a (void function)
	//pre: requires successful calculations and data gathering
	//post: yeilds both cout and ofstream output

void closefiles(ifstream & salesf, ifstream & productf, ofstream & outfile, ofstream & errorfile);
	//openfiles() calls ifstream and ofstream values to close all files
	//return type: n/a (void function)
	//pre: requires files to be open prior to function call
	//post: closes all opened files

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
    
	bonuscalc(salesdata, productdata, salescount, prodcount);
	outputdata(outfile, salesdata, productdata, salescount, prodcount);
	closefiles(salesf, productf, outfile, errorfile);
	return 0;
}
//************************************************************************************
bool openfiles(ifstream & salesf, ifstream & productf, ofstream & outfile, ofstream & errorfile) {
	//openfiles() calls ifstream and ofstream values to open both input and output files
	//return type: bool (true/false)
	//pre: fstream variable declaration, a positive file open result
	//post: yields a bool output value that determines whether or not the rest of the program will carry on

	string salesname, productname, outputname;
	cout << "Please tell me your sales file name.\n";
	cin >> salesname;
	salesf.open(salesname.c_str());
	cout << "Please tell me your product file name.\n";
	cin >> productname;
	productf.open(productname.c_str());
	cout << "Please name your outfile file.\n";
	cin >> outputname;
	outfile.open(outputname.c_str());
	//productf.open("products.txt");
	//salesf.open("salesFile.txt");
	//outfile.open("Outputfile.txt");
	errorfile.open("Errorfile.txt");
    if (! productf.is_open()) { return false; }
	if (! salesf.is_open()) { return false; }
    if (! outfile.is_open()) { return false; }
	if (! errorfile.is_open()) { return false; }
    return true;
}
//************************************************************************************
//************************************************************************************
void readprod(ifstream & productf, productType productdata[], int & prodcount) {
	//readprod() calls the input product file data and assigns a variable to each value passed
	//return type: n/a (void function)
	//pre: requires successful ifstream procedure
	//post: passes values for product structure

    while (productf) {
        productf >> productdata[prodcount].productnum >> productdata[prodcount].price;
        prodcount++;
    }
}
//************************************************************************************
void readsales(ifstream & salesf, ofstream & errorfile, salesType salesdata[], productType productdata[], int & salescount, int prodcount) {
	//readsales() calls the input sales file data and assigns a variable to each value passed
	//return type: n/a (void function)
	//pre: requires successful ifstream procedure
	//post: passes values for sales structure; also passes errorfile into the ofstream

	int i = 0;
	int productnum;
	int qty;
	
	while (salesf) {
        salesf 	>> 	salesdata[salescount].firstname >> salesdata[salescount].lastname >> salesdata[salescount].id >> productnum;

		while (productnum != -1) {
            salesf	>>	qty;

            int found = 0;
            for (i = 0; i < prodcount; i++) {
				if (productnum==productdata[i].productnum) {
					found = 1;
					salesdata[salescount].totalsales += (qty * productdata[i].price);
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
void bonuscalc(salesType salesdata[], productType productdata[], int salescount, int prodcount) {
	//bonuscalc() uses sales structure data passed from readsales() to calculate the sales bonus
	//return type: n/a (void function)
	//pre: requires successful calculation of salesdata[].totalsales
	//post: passes a value for salesdata[].bonus

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
}
//************************************************************************************
void outputdata(ofstream & outfile, salesType salesdata[], productType productdata[], int salescount, int prodcount) {
	//outputdata() uses all the calculated data to output everything in an organized format
	//return type: n/a (void function)
	//pre: requires successful calculations and data gathering
	//post: yeilds both cout and ofstream output

	cout 	<< setw(12) << left << "First Name" << setw(13) << left << "Last Name" 	<< setw(8) << left << "ID"
			<< setw(14) << left << "Total Sales"<< setw(14) << left << "Bonus"		<< endl;
	cout	<< left		<< "=====================================================================\n";
	outfile << setw(12) << left << "First Name" << setw(13) << left << "Last Name" 	<< setw(8) << left << "ID"
			<< setw(14) << left << "Total Sales"<< setw(14) << left << "Bonus"		<< endl;
	outfile	<< left		<< "=====================================================================\n";
	int i=0;
	for (i = 0; i < (salescount-1); i++) {
		cout	<<	fixed 	<< showpoint 	<< setprecision(2);
		cout	<<	setw(12)<< left			<< salesdata[i].firstname       //<< " "
				<<	setw(13)<< left			<< salesdata[i].lastname        //<< " "
				<<	setw(8)<< left			<< salesdata[i].id              //<< " "
				<<	setw(1) << left			<< "$"	<<	setw(13)            << left << salesdata[i].totalsales //<< " "
				<<	setw(1) << left			<< "$"  <<	setw(12)            << left << salesdata[i].bonus   << "\n";
		outfile	<<	fixed 	<< showpoint 	<< setprecision(2);
		outfile	<<	setw(12)<< left			<< salesdata[i].firstname       //<< " "
				<<	setw(13)<< left			<< salesdata[i].lastname        //<< " "
				<<	setw(8)<< left			<< salesdata[i].id              //<< " "
                <<	setw(1) << left			<< "$"	<<	setw(13)            << left << salesdata[i].totalsales //<< " "
                <<	setw(1) << left			<< "$"  <<	setw(12)            << left << salesdata[i].bonus   << "\n";
	}
}
//************************************************************************************
//************************************************************************************
void closefiles(ifstream & salesf, ifstream & productf, ofstream & outfile, ofstream & errorfile) {
	//openfiles() calls ifstream and ofstream values to close all files
	//return type: n/a (void function)
	//pre: requires files to be open prior to function call
	//post: closes all opened files

    productf.close();
	salesf.close();
	outfile.close();
	errorfile.close();
}
