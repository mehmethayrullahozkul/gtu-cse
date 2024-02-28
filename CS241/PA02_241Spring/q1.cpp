#include <iostream>
#include <string>
#include<sstream>
#include<fstream>
using namespace std;

enum RETURN_CODES {SUCCES, CANT_FIND_IMAGE, IMAGE_CORRUPTED, INVALID_IMAGE_HEADER, IMAGE_FORMAT_CANT_BE_USED, NO_IMAGE_LOADED, CANT_CREATE_IMAGE, INVALID_COEFFICENTS};

string AVAILABLE_FORMATS[1] = {"P3"};
bool ERROR = false;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IMAGE {

    private:

        string format;
        int rows, columns;
        int max_color_value;
        int *image = NULL;

    public:

        // Using constructor for default values.
        IMAGE() 
        {
            format = "P3";
            max_color_value = 255;
        }

        // Allocating memory for the image.
        void setImage(int r, int c)
        {
            image = new int[r * c * 3]; 
        }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        int openImage()
        {

            // Declaring variables to store the readen values.
            string word;
            string IMAGE_NAME;
            int r, c, m_c;
            int readen_color;
        

            cin>>IMAGE_NAME;


            // If cant open the image file, throw error.
            ifstream getImage(IMAGE_NAME);
            if(getImage.fail())
            {   
                return CANT_FIND_IMAGE;
            }


            // Getting the first read, image's format.
            getImage >> word;

            

            // Checking the readen format from file with comparing it with AVAILABLE_FORMATS array we declared globally.
            ERROR = true;
            for(string s : AVAILABLE_FORMATS)
            {
                if(!s.compare(word))
                    {ERROR=false;break;}
            }
            if(ERROR)
            {
                return IMAGE_FORMAT_CANT_BE_USED;
            }

            format = word;

            // Getting row, column and max color value from the file.
            getImage>>r>>c>>m_c;
            rows = r;
            columns = c;
            max_color_value = m_c;


            // If any of the readen values are below 0, throw some error.
            if(r < 0 || c < 0 || m_c < 0)
            {
                return INVALID_IMAGE_HEADER;
            }


            // Calling the setImage function for allocating the memory for the image.
            setImage(r, c);


            // Reading the Red, Green, Blue values from the file and filling up the image object with it.
            for(int a = 0 ; a < columns ; a++ )
            {
                for(int b = 0 ; b < rows ; b++ )
                {
                    for(int x = 0 ; x < 3 ; x++ )
                    {
                        getImage>>readen_color;
                        //cout<<b*(c-1) + (a*((r-1)*c)) + x <<" : "<<R<<" / "<<endl;
                        image[b*(columns-1) + (a*((rows-1)*columns)) + x] = readen_color;
                    }
                    
                }
            }
            return SUCCES;
        }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        int saveImageData() 
        {
            // If no image loaded yet, throw error.
            if(image == NULL)
            {
                return NO_IMAGE_LOADED;
            }


            // Getting the image name gonna be saved.
            string IMAGE_NAME;
            cin>>IMAGE_NAME;


           // If cant create the image file, throw some error.
            ofstream setImage(IMAGE_NAME);
            if(setImage.fail())
            {   
                return CANT_CREATE_IMAGE;
            }


            // After creating succesfully, begin to write header of the image.
            setImage<<format<<endl;
            setImage<<rows<<" "<<columns<<endl;
            setImage<<max_color_value<<endl;
            

            // Lastly, write the rgb values to the file.
            for(int a = 0 ; a < columns ; a++ )
            {
                for(int b = 0 ; b < rows ; b++ )
                {
                    // writing values 3 by 3 as x, x+1, x+2
                    setImage<<
                    image[(b*(columns-1) + (a*((rows-1)*columns)))]<<" "<<
                    image[(b*(columns-1) + (a*((rows-1)*columns))) + 1]<<" "<<
                    image[(b*(columns-1) + (a*((rows-1)*columns))) + 2]<<
                    " \t";  
                }
                setImage<<endl;
            }
            return SUCCES;
        }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        int convertToGrayScale() {

            int ZERO_COUNT = 0;
            int WORD_COUNT = 0;

            // If no image loaded yet, throw error.
            if(image == NULL)
            {
                return NO_IMAGE_LOADED;
            }

            std::string coef_input;

            // Ignoring the last character in case any problem for std::getline()
            cin.ignore();

            // Getting user input as a line.
            std::getline(std::cin, coef_input);


            // Checking input if there's any other character than numbers, dot and space.
            for(int i = 0 ; i < coef_input.length() ; i++ )
            {
                if((coef_input[i] > '9' || coef_input[i] < '0') && coef_input[i] != '.' && coef_input[i] != ' ')
                {
                    return INVALID_COEFFICENTS;
                }
                if(coef_input[i] == '0')
                {
                    ZERO_COUNT++;
                } 
            }

            // There must be 3 '0' in the input if not, throw error.
            if(ZERO_COUNT != 3)
            {
                return INVALID_COEFFICENTS;
            }

            istringstream input(coef_input);
            
            string coefficent;
            float cf[10];


            // This right here tries to convert strings from user input to float, if cant throw error.
            while(input>>coefficent) {
                try {
                    cf[WORD_COUNT] = std::stof(coefficent);
                }
                catch (const std::invalid_argument&) {
                    return INVALID_COEFFICENTS;
                } 
                catch (const std::out_of_range&) {
                    return INVALID_COEFFICENTS;
                }
                WORD_COUNT++;
            }

            // If user entered more than 3 words, throw error.
            if(WORD_COUNT != 3)
            {
                return INVALID_COEFFICENTS;
            }


            // If any number is bigger than 1 or less than 0, throw error.
            for(int i = 0 ; i < 3 ; i++ ) 
            {
                if(cf[i] < 0.0 || cf[i] >= 1.0)
                {
                    return INVALID_COEFFICENTS;
                }
            }

            int x, y, z, p;
            for(int a = 0 ; a < columns ; a++ )
            {
                for(int b = 0 ; b < rows ; b++ )
                {
                    // I have used x,y,z,p variables for more readable code.

                    // Red value stored in array.
                    x = image[(b*(columns-1) + (a*((rows-1)*columns)))];

                    // Green value stored in array.
                    y = image[(b*(columns-1) + (a*((rows-1)*columns))) + 1]; 

                    // Blue value stored in array.
                    z = image[(b*(columns-1) + (a*((rows-1)*columns))) + 2];

                    // Converting to grayscale whilst using static cast for float to int conversion.
                    p = static_cast<int>(static_cast<float>(x) * cf[0]) + (static_cast<float>(y) * cf[1]) + (static_cast<float>(z) * cf[2]);

                    // if grayscale conversion results bigger than 255, make it 255.
                    if(p > 255) {p = 255;}


                    // Make all three rgb values to 'p'.
                    image[(b*(columns-1) + (a*((rows-1)*columns)))] = p;
                    image[(b*(columns-1) + (a*((rows-1)*columns))) + 1] = p;
                    image[(b*(columns-1) + (a*((rows-1)*columns))) + 2] = p;
                }
            }

            return SUCCES;

        }

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main() {

    string MENU_SELECT = " ";
    string SUB_MENU_SELECT = " ";
    int RETURN_CODE;

    IMAGE yenidunya;

    while(MENU_SELECT.compare("0"))
    {
        cout<<"MAIN MENU"<<endl;
        cout<<"0 - Exit"<<endl;
        cout<<"1 - Open An Image(D)"<<endl;
        cout<<"2 - Save Image Data(D)"<<endl;
        cout<<"3 - Scripts(D)"<<endl;

        cin>>MENU_SELECT;

        // If user wishes to quit the program.
        if (!MENU_SELECT.compare("0")) 
        {
            cout<<endl<<"quitting the program... see you around!"<<endl;
        }

        // If user wishes to load an image.
        else if (!MENU_SELECT.compare("1")) 
        {

            SUB_MENU_SELECT = " ";

            while(SUB_MENU_SELECT.compare("0"))
            {

                cout<<"OPEN AN IMAGE MENU"<<endl;
                cout<<"0 - UP"<<endl;
                cout<<"1 - Enter A File Name"<<endl;
                cin>>SUB_MENU_SELECT;

                // User goes to upper main menu.
                if(!SUB_MENU_SELECT.compare("0")) 
                {
                    break;
                }

                // User going to enter a file name.
                else if(!SUB_MENU_SELECT.compare("1"))
                {
                    
                    RETURN_CODE = yenidunya.openImage();
                    switch(RETURN_CODE) 
                    {
                        case CANT_FIND_IMAGE:
                            cout<<"The image could not be opened, make sure to enter to right file name."<<endl;
                            break;
                        case IMAGE_FORMAT_CANT_BE_USED:
                            cout<<"The image can not be used, image's format is not in the available format's list."<<endl;
                            break;
                        case INVALID_IMAGE_HEADER:
                            cout<<"The image could not loaded, invalid header information."<<endl;
                            break;
                        case SUCCES:
                            cout<<"The image has opened succesfully."<<endl;
                            break;
                        
                    }
                }

                // Invalid input in menu, throw error. 
                else 
                {
                    cout<<" "<<endl<<"Error, please enter a valid option."<<endl;
                }
            }
        }


        // If user wishes to save the image.
        else if (!MENU_SELECT.compare("2")) 
        {
            SUB_MENU_SELECT = " ";

            while(SUB_MENU_SELECT.compare("0"))
            {

                cout<<"SAVE IMAGE DATA MENU"<<endl;
                cout<<"0 - UP"<<endl;
                cout<<"1 - Enter The Name Of The Image File"<<endl;
                cin>>SUB_MENU_SELECT;

                // User redirects to upper menu.
                if(!SUB_MENU_SELECT.compare("0")) 
                {
                    break;
                }

                // User enters a file name.
                else if(!SUB_MENU_SELECT.compare("1"))
                {
                    RETURN_CODE = yenidunya.saveImageData();
                    switch(RETURN_CODE) 
                    {
                        case CANT_CREATE_IMAGE:
                            cout<<"The image could not be saved, please try again."<<endl;
                            break;
                        case NO_IMAGE_LOADED:
                            cout<<"No image has loaded yet, please load an image first."<<endl;
                            break;
                        case SUCCES:
                            cout<<"The image has saved succesfully."<<endl;
                            break;
                        
                    }
                } 
                // User didnt enter any submenu inputs, throw error.
                else 
                {
                    cout<<" "<<endl<<"Error, please enter a valid option."<<endl;
                }
            }
        }


        // If user wishes to use converting grayscale script.
        else if (!MENU_SELECT.compare("3"))
{
            SUB_MENU_SELECT = " ";

            while(SUB_MENU_SELECT.compare("0"))
            {

                cout<<"CONVERT TO GRAYSCALE MENU"<<endl;
                cout<<"0 - UP"<<endl;
                cout<<"1 - Enter Coefficients For RED GREEN And BLUE Channels."<<endl;
                cin>>SUB_MENU_SELECT;

                // User redirects to upper menu.
                if(!SUB_MENU_SELECT.compare("0")) 
                {
                    break;
                }

                // Program calls to grayscale script.
                else if(!SUB_MENU_SELECT.compare("1"))
                {
                    RETURN_CODE = yenidunya.convertToGrayScale();
                    switch(RETURN_CODE) 
                    {
                        case INVALID_COEFFICENTS:
                            cout<<"The coefficents entered should between [0,1) and 3 at a time."<<endl;
                            break;
                        case NO_IMAGE_LOADED:
                            cout<<"No image has loaded yet, please load an image first."<<endl;
                            break;
                        case SUCCES:
                            cout<<"The image has converted succesfully."<<endl;
                            break;
                        
                    }
                }
                // User didnt enter any of the submenu inputs, throw error. 
                else 
                {
                    cout<<" "<<endl<<"Error, please enter a valid option."<<endl;
                }
            }
        }
        // User didnt enter any of the menu inputs, throw error.
        else
        {
            cout<<" "<<endl<<"Error, please enter a valid option."<<endl;
        }
    }
}


