
#include "Sigmoid_bp_ann.h"

void main(void) {
    // declare program variables
     bool bNot_done;
	 char cRaw_menu_response;
     int iMenu_response = 0;
     char cPause = 0;
	 // a bp_ann instance
	 bp_ann clBP_network;

    // initialize the loop variable to TRUE
     bNot_done = true;

    // loop until the loop variable is FALSE
     while(bNot_done) {

        // display the menu
          cout << endl << endl;
            // menu selections:
			cout << "==============================================================" << endl;
            // 1) train bp_ann - resets network weights
            cout << "1) Train a bp_ann" << endl;
            // 2) test bp_ann
            cout << "2) Test the bp_ann" << endl;
            // 3) retrain bp_ann without reseting weights
			cout << "3) Retrain the bp_ann without reseting weights" << endl;
			// 4) save the bp_ann data
            cout << "4) Save the bp_ann data" << endl;
			// 5) reload a saved bp_ann
			cout << "5) Reload a saved bp_ann" << endl;
            // 9) quit the program
            cout << "9) Quit the program" << endl << endl << endl;
			// prompt for the user's menu choice
			cout << "What is your selection (1 - 5 or 9)? --> ";
            // get the menu selection
            cin >> cRaw_menu_response;
			// filter for bad input - convert to an integer
			iMenu_response = (int)cRaw_menu_response;
			// offset to actual integer menu selections - all other values are unacceptable
			iMenu_response = iMenu_response - 48;
			// setup for next interaction
			cout << endl;
			cout << "==============================================================" << endl;
			cout << endl << endl;

          // switch statement to act on the menu selection
            switch(iMenu_response){
               // case 1 - train bp_ann - resets network weights
               case 1:
                    // 
				   clBP_network.train_bp_ann();
                    break;
               // case 2 - test bp_ann
               case 2:
					// 
				   clBP_network.test_bp_ann();
                    break;
               // case 3 - retrain bp_ann without reseting weights
               case 3:
                    // 
				   clBP_network.retrain_bp_ann();
                    break;
				// case 4 - save the bp_ann data
               case 4:
                    // 
				   clBP_network.save_bp_ann();
                    break;
				//case 5 - reload a saved bp_ann
			   case 5:
				   //
				   clBP_network.reload_bp_ann();
				   break;
               // case 9 - set the loop variable to FALSE
               case 9:
                    bNot_done = false;
                    break;
               // default - display error message to screen and 
               //             re-display menu
               default:
                    cout << "That is an invalid selection. Try again." << endl << endl;
            }// switch

     }// while - end the loop

    return;
} // main

//***********************************************************************
