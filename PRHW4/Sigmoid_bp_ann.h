

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;

class data_instance {


public:
	vector<float> vfData;
	vector<float> vfClassification;
    
	// public methods
	data_instance(void); // class constructor

}; 
data_instance::data_instance(void) {

	return;
} 
class bp_ann {

	// private class variables
	vector<data_instance> vclTraining_data;
	vector<data_instance> vclOutput_data;
	vector<data_instance> vclTest_data;
	//vector<data_instance> vclTest_output_data;
	vector<float> vfInput_layer;
	vector<float> vfHidden_layer;
	vector<float> vfOutput_layer;
	vector<float> vfOutput_error;
	vector<float> vfHidden_error;
	vector< vector<float> > vvfFirst_network_layer;
	vector< vector<float> > vvfSecond_network_layer;
	int iMax_weight;
	int iTraining_iterations;
	float fActiviation_rate;
	float fLearning_rate; // Mitchell p 88 & 98
	float fMomentum_rate;  // Mitchell p 100
	int iInput_layer_node_count;
	int iHidden_layer_node_count;
	int iOutput_layer_node_count;
	int iTraining_session;
	float fTraining_factor;
	string sTraining_data_fname;
	string sTest_data_fname;
	
	// private methods
	void read_control_file(void);
	void read_training_data(void);
	void read_test_data(void);
	void initialize_network(void);
	int Random_value(int iRange);
	float activation_function(float fInput);
	void first_network_layer_trg(int iIndx);
	void first_network_layer_tst(int iIndx);
	void second_network_layer(void);
	void compute_classification_error(int iIndex);
	void train_second_network_layer(void);
	void train_first_network_layer(void);
	void evaluate_test_data(int iIndex);
	void save_test_results(void);
	string ToString(int iValue);

public:
	// public class variables
    
	// public methods
	bp_ann(void);
	void train_bp_ann(void);
	void test_bp_ann(void);
	void retrain_bp_ann(void);
	void save_bp_ann(void);
	void reload_bp_ann(void);

}; 
bp_ann::bp_ann(void) {

	iMax_weight = 100;
	iTraining_iterations = 0;
	fLearning_rate = 1.0;
	fMomentum_rate = 1.0;
	iInput_layer_node_count = 0;
	iHidden_layer_node_count = 0;
	iOutput_layer_node_count = 0;
	fTraining_factor = 1;
	iTraining_session = 0;

	return;
} 
void bp_ann::train_bp_ann(void) { 

	//local variables
	int iLoop_indx;
	int iInstance_indx;
	int iTraining_instance_ct;
	int iTest_instance_ct;
	
	// output two new line characters
	cout << endl << endl;

	// increment the training session count
	iTraining_session++;

	//read the control file
	read_control_file();

	//read the training data
	read_training_data(); //OK

	// read the test data
	read_test_data();

	//initialize the network
	initialize_network(); //OK

	// get the number of training instances
	iTraining_instance_ct = (int)vclTraining_data.size();


	for(iLoop_indx=0; iLoop_indx < iTraining_iterations; iLoop_indx++) {

		//feed training set to the network collecting the total error
		for(iInstance_indx = 0; iInstance_indx < iTraining_instance_ct; iInstance_indx++){

			first_network_layer_trg(iInstance_indx); // OK

			second_network_layer( ); // OK

			compute_classification_error(iInstance_indx); // OK

			//adjust the network weights using the output error
			train_second_network_layer( ); // OK
			train_first_network_layer( ); // OK

		} // for

	} //end training loop

	// output two new line characters
	cout << endl << endl;

	// get the number of test instances
	iTest_instance_ct = (int)vclTest_data.size();
	
	//feed training set to the network - to generate network results - final error values
	for(iInstance_indx = 0; iInstance_indx < iTest_instance_ct; iInstance_indx++){
		
		first_network_layer_tst(iInstance_indx); //OK

		second_network_layer( ); // OK

		//save each data instance with its classification results
		evaluate_test_data(iInstance_indx); // OK
	} // for
	
	//report the last output error results
	save_test_results();

	return;
	
} // bp_ann::train_bp_ann

//*************************************************************************
void bp_ann::test_bp_ann(void) {

	

	return;
	
} 

//*************************************************************************
void bp_ann::retrain_bp_ann(void) {

	//local variables
	int iTraining_iterations = 0;
	int iLoop_indx;
	int iInstance_indx;
	int iTraining_instance_ct;
	int iTest_instance_ct;

	// increment the training session count
	iTraining_session++;

	//we assume that we have an existing trained network in the application

	cout << "===========================================================";
	cout << endl;
	cout << "This menu choice will continue to train the network with ";
	cout << "the current parameter settings and training data. You ";
	cout << "will be asked to identify the number of training ";
	cout << "iterations for this retraining session." << endl;
	cout << "===========================================================";
	cout << endl << endl;

	// get the number of training iterations
	cout << "How many training iterations do you want? ";
	cin >> iTraining_iterations;
	cout << endl << endl;
	
	//get the training data filename
	// NOT USED - will use current data
	
	//read the training data
	// NOT USED - will use current data
	
	//NOTE: there are two main training techniques
		//1) train the network using the error for each training set member
		//2) train the network using the total error for the entire training set
			
	//this implementation will use the first method for training

	// get the number of training instances
	iTraining_instance_ct = (int)vclTraining_data.size();

	//training loop - controlled by a fixed number of iterations
	for(iLoop_indx = 0; iLoop_indx < iTraining_iterations; iLoop_indx++) {
	
		//feed training set to the network collecting the total error
		for(iInstance_indx = 0; iInstance_indx < iTraining_instance_ct; iInstance_indx++){

			first_network_layer_trg(iInstance_indx); // OK

			second_network_layer( ); // OK

			compute_classification_error(iInstance_indx); // OK

			//adjust the network weights using the output error
			train_second_network_layer( ); // OK
			train_first_network_layer( ); // OK

		} // for

	} //end training loop

	// output two new line characters
	cout << endl << endl;

	// get the number of test instances
	iTest_instance_ct = (int)vclTest_data.size();
	
	//feed training set to the network - to generate network results - final error values
	for(iInstance_indx = 0; iInstance_indx < iTest_instance_ct; iInstance_indx++){
		
		first_network_layer_tst(iInstance_indx); //OK

		second_network_layer( ); // OK

		//save each data instance with its classification results
		evaluate_test_data(iInstance_indx); // OK
	} // for
	
	//report the last output error results
	save_test_results();

	return;

} // bp_ann::retrain_bp_ann

//*************************************************************************
void bp_ann::save_bp_ann(void) {

	//local variables
	string sOutput_fname;
	
	//get the filename to save the network to
	cout << "What output filename do you want to use? ";
	cin >> sOutput_fname;
	cout << endl << endl << endl;
	
	//open the output file
	
	//save the network data
	
		//save the input layer node count
		//save the hidden layer node count
		//save the output layer node count
		
		//save the first layer network weignts
		//save the second layer network weights
		
	//close the output file

	return;

} // bp_ann::save_bp_ann

//*************************************************************************
void bp_ann::reload_bp_ann(void) {

	//local variables
	
	//get the filename to read the network from
	
	//open the input file
	
	//read the network data
	
		//read the input layer node count
		//read the hidden layer node count
		//read the output layer node count
		
		//read the first layer network weignts
		//read the second layer network weights
		
	//close the input file

	return;

} // bp_ann::reload_bp_ann

//*************************************************************************
void bp_ann::read_control_file(void) {

	// local variables

    // declare an input stream to read the data
	ifstream strInput_stream;

    // modify the filename
    string sFilename = "control.dat";

	// open the input stream to read the key
	strInput_stream.open(sFilename.c_str());

    // check if the file was OK
    if (strInput_stream.is_open()){

		//read input layer node count
        strInput_stream >> iInput_layer_node_count;

		//read hidden layer node count
        strInput_stream >> iHidden_layer_node_count;

		//read output layer node count
        strInput_stream >> iOutput_layer_node_count;
		
		//read training iteration count
        strInput_stream >> iTraining_iterations;

		//read learning rate
        strInput_stream >> fLearning_rate;
		
		//read momentum value
        strInput_stream >> fMomentum_rate;

		// read activation rate
		strInput_stream >> fActiviation_rate;
		
		//read training data filename
        strInput_stream >> sTraining_data_fname;

		//read test data filename
        strInput_stream >> sTest_data_fname;

    } //if
    
    else cout << "Error reading the control file!" << endl << endl; // print error message
	
	//close the input filestream for the control file
	strInput_stream.close();  // close filestream

    return;

} // bp_ann::read_control_file

//*************************************************************************
void bp_ann::initialize_network(void) {

	// local variables 
	int iIndx;
	int iLoop_index1, iLoop_index2;

	//initialize the dimension of the input_layer
	vfInput_layer.resize(iInput_layer_node_count);
	
	//initialize the dimension of the hidden_layer
	vfHidden_layer.resize(iHidden_layer_node_count);

	// initialize the dimension of the hidden layer error vector
	vfHidden_error.resize(iHidden_layer_node_count);

	//initialize the dimension of the output_layer
	vfOutput_layer.resize(iOutput_layer_node_count);

	// initialize the dimension of the output layer error vector
	vfOutput_error.resize(iOutput_layer_node_count);
	
	//initialize the dimensions of the first network layer
	//initialize the rows first
	vvfFirst_network_layer.resize(iInput_layer_node_count);
	//now the columns
	for(iIndx = 0; iIndx < iInput_layer_node_count; iIndx++){
		vvfFirst_network_layer[iIndx].resize(iHidden_layer_node_count);
	} // for

	//insert random weights (between -0.5 and 0.5) into the first network layer
	for(iLoop_index1 = 0; iLoop_index1 < iInput_layer_node_count; iLoop_index1++){
		for(iLoop_index2 = 0; iLoop_index2 < iHidden_layer_node_count; iLoop_index2++){
			vvfFirst_network_layer[iLoop_index1][iLoop_index2] 
					= (((float)Random_value(iMax_weight)) - ((float)iMax_weight/2)) / 100;
		} // for
	} // for

	//initialize the dimensions of the second network layer
	//initialize the rows first
	vvfSecond_network_layer.resize(iHidden_layer_node_count);
	//now the columns
	for(iIndx = 0; iIndx < iHidden_layer_node_count; iIndx++){
		vvfSecond_network_layer[iIndx].resize(iOutput_layer_node_count);
	} //for
	
	//insert random weights (between -0.5 and 0.5) into the second network layer
	for(iLoop_index1 = 0; iLoop_index1 < iHidden_layer_node_count; iLoop_index1++){
		for(iLoop_index2 = 0; iLoop_index2 < iOutput_layer_node_count; iLoop_index2++){
			vvfSecond_network_layer[iLoop_index1][iLoop_index2] 
					= (((float)Random_value(iMax_weight)) - ((float)iMax_weight/2)) / 100;
		} // for
	} // for
	return;
} // bp_ann::initialize_network

//*************************************************************************
void bp_ann::read_training_data(void) {

    // local variables
    int iAttribute_ct;
	int iClassification_size;
    int iIndex;
	float fData_value = 0;
	unsigned uData_size;

	// declare an input stream to read the key
	ifstream strInput_stream;

    // declare data storage for the input data
    data_instance clInput_instance;

    // modify the filename
    sTraining_data_fname = sTraining_data_fname + ".dat";

	// open the input stream to read the key
	strInput_stream.open(sTraining_data_fname.c_str());

    // check if the file was OK
    if (strInput_stream.is_open()){

        // set the size of the data vector
		iAttribute_ct = iInput_layer_node_count;
        clInput_instance.vfData.resize(iAttribute_ct);

        // set the size of the classification vector
		iClassification_size = iOutput_layer_node_count;
        clInput_instance.vfClassification.resize(iClassification_size);

        while(!strInput_stream.eof()){

	        // get the attributes
            for(iIndex = 0; iIndex < iAttribute_ct; iIndex++){
	            strInput_stream >> clInput_instance.vfData[iIndex];
            } // for

	        // get the classification
            for(iIndex = 0; iIndex < iClassification_size; iIndex++){
	            strInput_stream >> clInput_instance.vfClassification[iIndex];
            } // for

            // save the data in the vector set
            vclTraining_data.push_back(clInput_instance);

            }// while

        } //if
    
    else cout << "Error reading the training data file!" << endl << endl; // print error message

	strInput_stream.close();  // close filestream

	// allocate memory for the output data
	uData_size = vclTraining_data.size();
	vclOutput_data.resize((int)uData_size);

	return;

} // bp_ann::read_training_data

//*************************************************************************
void bp_ann::read_test_data(void) {

	// local variables
    // local variables
    int iAttribute_ct;
	int iClassification_size;
    int iIndex;
	float fData_value = 0;
	string sTest_data_fname_local;

	// declare an input stream to read the key
	ifstream strInput_stream;

    // declare data storage for the input data
    data_instance clInput_instance;

    // modify the filename
    sTest_data_fname_local = sTest_data_fname + ".dat";

	// open the input stream to read the key
	strInput_stream.open(sTest_data_fname_local.c_str());

    // check if the file was OK
    if (strInput_stream.is_open()){

        // set the size of the data vector
		iAttribute_ct = iInput_layer_node_count;
        clInput_instance.vfData.resize(iAttribute_ct);

        // set the size of the classification vector
		iClassification_size = iOutput_layer_node_count;
        clInput_instance.vfClassification.resize(iClassification_size);

        while(!strInput_stream.eof()){

	        // get the attributes
            for(iIndex = 0; iIndex < iAttribute_ct; iIndex++){
	            strInput_stream >> clInput_instance.vfData[iIndex];
            } // for

	        // initialize the classification
            for(iIndex = 0; iIndex < iClassification_size; iIndex++){
	            strInput_stream >> clInput_instance.vfClassification[iIndex];
            } // for

            // save the data in the vector set
            vclTest_data.push_back(clInput_instance);

            }// while

        } //if
    
    else cout << "Error reading the training data file!" << endl << endl; // print error message

	strInput_stream.close();  // close filestream

	return;
} // bp_ann::read_test_data

//*************************************************************************
int bp_ann::Random_value(int iRange) {
	// this function returns an integer value between 0 and iRange

     // the local variables
     int iRand_val = 0;
     int iRand_num = 0;
	 static int iSeed_tries = 0; // seed only once per execution

     // initialize the PRNG - but only the first time
     if(iSeed_tries < 1) {
		srand( (unsigned)time( NULL ) );
		iSeed_tries++;
	 } // if

     // generate a random value
     iRand_num = rand();

     // generate the return value
     iRand_val = iRand_num % iRange;

     return(iRand_val);
} // bp_ann::Random_value

//*************************************************************************
float bp_ann::activation_function(float fInput){
	// this implements the SIGMOID activation function

	// local variables
	float fAnswer = 0;

	fAnswer = 1 / (1 + exp((-1) * (fActiviation_rate * fInput)));

	return (fAnswer);
} // bp_ann::activation_function

//*************************************************************************
//float bp_ann::activation_function(float fInput){
	// this implements the GAUSSIAN activation function

	// local variables
//	float fAnswer = 0;

//	fAnswer = exp(((-1) * (fInput * fInput)) / fActiviation_rate);

//	return (fAnswer);
//} // bp_ann::activation_function

//*************************************************************************
void bp_ann::first_network_layer_trg(int iIndx){

	// local variables
	int iInput_indx;
	int iHidden_indx;

	// populate the vfInput_layer
	for(iInput_indx = 0; iInput_indx < iInput_layer_node_count; iInput_indx++){
		vfInput_layer[iInput_indx] = vclTraining_data[iIndx].vfData[iInput_indx];
	} // for

	// loop through each hidden layer element
	for(iHidden_indx = 0; iHidden_indx < iHidden_layer_node_count; iHidden_indx++){

		// initialize the hidden layer element
		vfHidden_layer[iHidden_indx] = 0;

		// compute this hidden layer value
		for(iInput_indx = 0; iInput_indx < iInput_layer_node_count; iInput_indx++){

			vfHidden_layer[iHidden_indx] = vfHidden_layer[iHidden_indx] 
				+ (vfInput_layer[iInput_indx] 
					* vvfFirst_network_layer[iInput_indx][iHidden_indx]);

		} // for
	} // for

	// apply activation function to the hidden layer
	for(iHidden_indx = 0; iHidden_indx < iHidden_layer_node_count; iHidden_indx++){
		vfHidden_layer[iHidden_indx] = activation_function(vfHidden_layer[iHidden_indx]);
	} // for

	return;
} // bp_ann::first_network_layer_trg

//*************************************************************************
void bp_ann::first_network_layer_tst(int iIndx){

	// local variables
	int iInput_indx;
	int iHidden_indx;

	// populate the vfInput_layer
	for(iInput_indx = 0; iInput_indx < iInput_layer_node_count; iInput_indx++){
		vfInput_layer[iInput_indx] = vclTest_data[iIndx].vfData[iInput_indx];
	} // for

	// loop through each hidden layer element
	for(iHidden_indx = 0; iHidden_indx < iHidden_layer_node_count; iHidden_indx++){

		// initialize the hidden layer element
		vfHidden_layer[iHidden_indx] = 0;

		// compute this hidden layer value
		for(iInput_indx = 0; iInput_indx < iInput_layer_node_count; iInput_indx++){

			vfHidden_layer[iHidden_indx] = vfHidden_layer[iHidden_indx] 
				+ (vfInput_layer[iInput_indx] 
					* vvfFirst_network_layer[iInput_indx][iHidden_indx]);

		} // for
	} // for

	// apply activation function to the hidden layer
	for(iHidden_indx = 0; iHidden_indx < iHidden_layer_node_count; iHidden_indx++){
		vfHidden_layer[iHidden_indx] = activation_function(vfHidden_layer[iHidden_indx]);
	} // for

	return;
} // bp_ann::first_network_layer_tst

//*************************************************************************

void bp_ann::second_network_layer(void){ // 

	// local variables
	int iHidden_indx;
	int iOutput_indx;

	// loop through each output layer element
	for(iOutput_indx = 0; iOutput_indx < iOutput_layer_node_count; iOutput_indx++){

		// initialize the hidden layer element
		vfOutput_layer[iOutput_indx] = 0;

		// compute this hidden layer value
		for(iHidden_indx = 0; iHidden_indx < iHidden_layer_node_count; iHidden_indx++){

			vfOutput_layer[iOutput_indx] 
				= vfOutput_layer[iOutput_indx] 
					+ (vfHidden_layer[iHidden_indx] 
						* vvfSecond_network_layer[iHidden_indx][iOutput_indx]);
		} // for
	} // for

	// apply activation function to the hidden layer
	for(iOutput_indx = 0; iOutput_indx < iOutput_layer_node_count; iOutput_indx++){
		vfOutput_layer[iOutput_indx] = activation_function(vfOutput_layer[iOutput_indx]);
	} // for

	return;
} // bp_ann::second_network_layer

//*************************************************************************
void bp_ann::compute_classification_error(int iIndex){

	// local variables
	int iOutput_indx;
	int iHidden_indx;
	float fPropagate_error;
//	float fLayer_input_value; // gaussian
//	int iInput_indx; // gaussian

	// calculate the error at the output layer
	for(iOutput_indx = 0; iOutput_indx < iOutput_layer_node_count; iOutput_indx++){

		// out_error = (ti - oi) (oi (1 - oi)) - sigmoid version
		vfOutput_error[iOutput_indx] = 
			(vclTraining_data[iIndex].vfClassification[iOutput_indx] - vfOutput_layer[iOutput_indx])
			* (vfOutput_layer[iOutput_indx] * (1 - vfOutput_layer[iOutput_indx]));
			
	} // for

	// calculate the error at the hidden layer
	for(iHidden_indx = 0; iHidden_indx < iHidden_layer_node_count; iHidden_indx++){
		
		// initialize fPropagate_error
		fPropagate_error = 0;

		// calculate the output error propagated back to the hidden layer
		for(iOutput_indx = 0; iOutput_indx < iOutput_layer_node_count; iOutput_indx++){

			// prop_error = Sum (w(2d layer) * out_error)
			fPropagate_error = fPropagate_error 
				+ (vfOutput_error[iOutput_indx] * vvfSecond_network_layer[iHidden_indx][iOutput_indx]);
		} // for

		// calculate the error at the hidden layer -> hid_error = prop_error (oh (1 - oh))
		vfHidden_error[iHidden_indx] = 
			fPropagate_error * (vfHidden_layer[iHidden_indx] * (1 - vfHidden_layer[iHidden_indx]));

	} // for

	return;
} // bp_ann::compute_classification_error

//*************************************************************************
void bp_ann::train_second_network_layer(void){
		//adjust the network weights using the output error (total error method)

	// local variables
	int iInput_indx;
	int iOutput_indx;

	// adjust the weights
	for(iInput_indx = 0; iInput_indx < iHidden_layer_node_count; iInput_indx++){ // the rows (inputs)
		for(iOutput_indx = 0; iOutput_indx < iOutput_layer_node_count; iOutput_indx++) { // the columns (outputs)

			vvfSecond_network_layer[iInput_indx][iOutput_indx] = 
				vvfSecond_network_layer[iInput_indx][iOutput_indx] 
				+ (vfOutput_error[iOutput_indx] * vfHidden_layer[iInput_indx] * fLearning_rate);

		} // for
	} // for

	return;
} // bp_ann::train_second_network_layer

//*************************************************************************
void bp_ann::train_first_network_layer(void){
		//adjust the network weights using the output error (total error method)

	// local variables
	int iInput_indx;
	int iOutput_indx;

	// adjust the weights
	for(iInput_indx = 0; iInput_indx < iInput_layer_node_count; iInput_indx++){ // the rows (inputs)
		for(iOutput_indx = 0; iOutput_indx < iHidden_layer_node_count; iOutput_indx++) { // the columns (outputs)

			vvfFirst_network_layer[iInput_indx][iOutput_indx] = 
				vvfFirst_network_layer[iInput_indx][iOutput_indx] 
				+ (vfHidden_error[iOutput_indx] * vfInput_layer[iInput_indx] * fLearning_rate);

		} // for
	} // for

	return;
} // bp_ann::train_first_network_layer

//*************************************************************************
void bp_ann::evaluate_test_data(int iIndex){

	// local variables
	int iOutput_indx;

	// calculate the test data classification accuracy
	for(iOutput_indx = 0; iOutput_indx < iOutput_layer_node_count; iOutput_indx++){

		// save the network classification for the test data
		vclTest_data[iIndex].vfClassification[iOutput_indx] = vfOutput_layer[iOutput_indx];

// ============================================================================
// there are several methods to score the classification accuracy. I decided to 
//  not evaluate the accuracy here. I will output the actual classification
//  values and eveluate the accuracy off-line. this chouce allows me to choose
//  whatever evaluation method that is appropriate for the data used.
// ============================================================================

	} // for

	return;

} // bp_ann::evaluate_test_data

//*************************************************************************
void bp_ann::save_test_results(void){
    
	// local variables
    unsigned uIndex1;
	int iIndex2, iIndex3;
	string sTest_data_output_fname;

    // modify the filename
	sTest_data_output_fname = sTest_data_fname + ToString(iTraining_session) + ".out";

	// declare an output stream 
	ofstream strResults_out_stream;

	// open the stream to write the output plaintext
	strResults_out_stream.open(sTest_data_output_fname.c_str());

    // loop through each test data instance
	for(uIndex1 = 0; uIndex1 < vclTest_data.size(); uIndex1++){

        // output the attributes
		for(iIndex2 = 0; iIndex2 < iInput_layer_node_count; iIndex2++){
            strResults_out_stream << vclTest_data[uIndex1].vfData[iIndex2];
            strResults_out_stream << " ";
        } // for

		for(iIndex3 = 0; iIndex3 < iOutput_layer_node_count; iIndex3++){
            strResults_out_stream << vclTest_data[uIndex1].vfClassification[iIndex3];
            strResults_out_stream << " ";
        } // for

	    // output a new line character
        strResults_out_stream << endl;

    } // for

	strResults_out_stream.close();

	return;
} // bp_ann::save_test_results(void)

//*************************************************************************
string bp_ann::ToString(int iValue){

	// local variables
	string sValue;

	if(iValue == 1) sValue = "1";
	if(iValue == 2) sValue = "2";
	if(iValue == 3) sValue = "3";
	if(iValue == 4) sValue = "4";
	if(iValue == 5) sValue = "5";
	if(iValue == 6) sValue = "6";
	if(iValue == 7) sValue = "7";
	if(iValue == 8) sValue = "8";
	if(iValue == 9) sValue = "9";
	if(iValue == 10) sValue = "10";
	if(iValue == 11) sValue = "11";
	if(iValue == 12) sValue = "12";
	if(iValue == 13) sValue = "13";
	if(iValue == 14) sValue = "14";
	if(iValue == 15) sValue = "15";
	if(iValue == 16) sValue = "16";
	if(iValue == 17) sValue = "17";
	if(iValue == 18) sValue = "18";
	if(iValue == 19) sValue = "19";
	if(iValue == 20) sValue = "20";
	if(iValue == 21) sValue = "21";
	if(iValue > 21) sValue = "XX";

	return(sValue);
} // bp_ann::ToString

//*************************************************************************




