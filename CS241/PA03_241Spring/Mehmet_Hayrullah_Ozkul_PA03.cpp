#include <iostream>
#include <string>
#include<sstream>
#include<fstream>
using namespace std;

enum RETURN_CODES {FAIL = 0, SUCCES = 1, CANT_FIND_IMAGE, 
                        IMAGE_CORRUPTED, INVALID_IMAGE_HEADER, IMAGE_FORMAT_CANT_BE_USED, 
                        NO_IMAGE_LOADED, CANT_CREATE_IMAGE, INVALID_COEFFICENTS};

string AVAILABLE_FORMATS[1] = {"P3"};
bool ERROR = false;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class ppmImage;


// Standalone functions
int read_ppm(const string source_ppm_file_name, ppmImage& destination_object);
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object);
int test_addition(const string filename_image1, const string filename_image2, const string filename_string3);
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_string3);
int test_print(const string filename_image1);
int swap_channels(ppmImage&  image_object_to_be_modified, int swap_choice);
ppmImage single_color(const ppmImage& source, int color_choice);


/* CLASS START */

class ppmImage {

    private:
        string file_name;
        string format;
        int rows, columns;
        int max_color_value;
        int *image; 

    public:
        int getMaxColor() const;
        void setMaxColor(int m);

        string getFormat() const;
        void setFormat(string s);

        int getRow() const;
        void setRow(int r);

        int getColumn() const;
        void setColumn(int c);

        int convertToGrayScale();
        void printDimension();

        void setFileName(string s);
        string getFileName() const;

        void allocateImage();

        int* getImage() const;


        /* Member functions to read and write image but didnt used in this assigment, they'r at the end of code. */
        
        int ppmsaveImageData();
        int openImage();

        

        // Default constructor
        ppmImage() 
        {
            format = "P3";
            max_color_value = 255;
            image = NULL;
            rows = 0;
            columns = 0;
            file_name = "";
        }

        // Constructor with filename.
        ppmImage(string ppmfile) {
            switch(read_ppm(ppmfile, *this))
            {
                case FAIL:
                    cout<<"Couldn't opened the image file named "<<ppmfile<<" ."<<endl;
                    break;
                case SUCCES:
                    cout<<"Succesfully created image with filename "<<ppmfile<<" ."<<endl;
                    break;
            }
        }

        // Constructor with row and column values.
        ppmImage(int r, int c) {
            // Setting up information.
            this->format = "P3";
            this->max_color_value = 255;
            this->rows = r;
            this->columns = c;
            this->image = new int[r * c * 3];
            for(int a = 0 ; a < r ; a++) 
            {
                for(int b = 0 ; b < c ; b++)
                {
                    for(int x = 0 ; x < 3 ; x++)
                    {
                        // Set them all to blank(white) pixels.
                        image[b*(columns-1) + (a*((rows-1)*columns)) + x] = 255;
                    }
                }
            }
        }

        // + operator overload

        const ppmImage operator+(const ppmImage &P) const;

        // - operator overload

        const ppmImage operator-(const ppmImage &P) const;

        // () operator overload

        int& operator()(int r, int c, int color) const;

        // << outstream operator overload
  
        friend ostream& operator<<(ostream&, ppmImage& c);

        // = assigment operator overload

        void operator=(const ppmImage &P);

};

/* CLASS END */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Getter and Setter functions to easy use.

int ppmImage::getMaxColor() const{
    return this->max_color_value;
}

string ppmImage::getFormat() const{
    return this->format;
}

void ppmImage::setMaxColor(int m) {
    this->max_color_value = m;
}

void ppmImage::setFormat(string s) {
    this->format = s;
}

int ppmImage::getRow() const{
    return this->rows;
}

void ppmImage::setRow(int r){
    this->rows = r;
}

int ppmImage::getColumn() const{
    return this->columns;
}

void ppmImage::setColumn(int c){
    this->columns = c;
}

void ppmImage::setFileName(string s) {
    this->file_name = s;
}

string ppmImage::getFileName() const{
    return this->file_name;
}


void ppmImage::allocateImage() {
    this->image = new int[rows * columns * 3];
}

int* ppmImage::getImage() const{
    return image;
}

void ppmImage::printDimension() {
    cout<<"Row value of image : "<<rows<<endl;
    cout<<"Column value of image : "<<columns<<endl;
}



/* OPERATOR OVERLOADS START */

// + operator overload

const ppmImage ppmImage::operator+(const ppmImage &P) const 
{
    if(rows != P.rows || columns != P.columns)
    {
        ppmImage A;
        return A;
    }
    else
    {
        int addition_result;
        int max = (getMaxColor() >= P.getMaxColor()) ? this->getMaxColor() : P.getMaxColor();
        ppmImage R(rows, columns);
        for(int a = 0 ; a < columns ; a++ )
        {
            for(int b = 0 ; b < rows ; b++ )
            {
                for(int x = 0 ; x < 3 ; x++ )
                {
    
                addition_result =  P.image[b*(columns-1) + (a*((rows-1)*columns)) + x] + this->image[b*(columns-1) + (a*((rows-1)*columns)) + x];
                if(addition_result > max) {addition_result = max;} // if result becomes more than 255, make it 255.
                R.image[b*(columns-1) + (a*((rows-1)*columns)) + x] = addition_result;
                }
    
            }
        }
        return R;
    }
}


// - operator overload

const ppmImage ppmImage::operator-(const ppmImage &P) const
{
    if(rows != P.rows || columns != P.columns)
    {
        ppmImage A;
        return A;
    }
    else
    {
        int subtraction_result;
        ppmImage R(rows, columns);
        for(int a = 0 ; a < columns ; a++ )
        {
            for(int b = 0 ; b < rows ; b++ )
            {
                for(int x = 0 ; x < 3 ; x++ )
                {
    
                subtraction_result = this->image[b*(columns-1) + (a*((rows-1)*columns)) + x] - P.image[b*(columns-1) + (a*((rows-1)*columns)) + x];
                if(subtraction_result < 0) {subtraction_result =  0;} // if result becomes under 0, make it 0.
                R.image[b*(columns-1) + (a*((rows-1)*columns)) + x] = subtraction_result;
                }
            }
        }
        return R;
    }
}

// () operator overload

int& ppmImage::operator()(int r, int c, int color) const
{
    return image[(r * (this->getColumn() - 1)) +  (c*(this->getRow()-1)*(this->getColumn())) + color - 1];
}

// << outstream operator overload

ostream& operator<<(ostream&, ppmImage& c)
{
    // printing out the information of image.
    int row = c.getRow();
    int column = c.getColumn();
    cout <<endl<<"Format : "<<c.getFormat()<<endl;
    cout<<"File name : ";
    if(c.getFileName() == "") {cout<<"this image has no recorded file name yet."<<endl;}
    else{cout<<c.getFileName()<<endl;}
    cout<<"Dimensions : Row = "<<row<<" Column = "<<c.getColumn()<<endl;
    int size = (row * column);
    for(int a = 0 ; a < row ; a++ )
    {
        for(int b = 0 ; b < column ; b++ )
        {
            cout<<c.image[a*column + b]<<" ";
            cout<<c.image[a*column + b + 1]<<" ";
            cout<<c.image[a*column + b + 2]<<" ";
            cout<<" \t";
        }
        cout<<endl;
    }
    cout<<endl;
    return cout;
}

// = assigment operator overload

void ppmImage::operator=(const ppmImage &P) {
    // copying values
    format = P.format;
    rows = P.rows;
    columns = P.columns;
    max_color_value = P.max_color_value;
    // if image is not null, then copy the image aswell with dynamic allocation
    if(P.image != NULL)
    {
        int size = rows * columns * 3;
        this->image = new int[size];
        for(int a = 0 ; a < size ; a++)
        {
            image[a] = P.image[a];
        }
    }
}

/* OPERATOR OVERLOAD END */



/* STANDALONE FUNCTIONS START */

int read_ppm(const string source_ppm_file_name, ppmImage& destination_object)
{
    // Declaring variables to store the readen values.
    string format;
    int r, c, m_c;
    int readen_color;
    // If cant open the image file, throw error.
    ifstream getImage(source_ppm_file_name);
    if(getImage.fail())
    {   
        getImage.close();
        return FAIL; // CANT_FIND_IMAGE
    }
    // Getting the first read, image's format.
    getImage >> format;
    
    // Checking the readen format from file with comparing it with AVAILABLE_FORMATS array we declared globally.
    ERROR = true;
    for(string s : AVAILABLE_FORMATS)
    {
        if(!s.compare(format))
            {ERROR=false;break;}
    }
    if(ERROR)
    {
        getImage.close();
        return FAIL; // IMAGE_FORMAT_CANT_BE_USED
    }
    destination_object.setFormat(format);

    // Getting row, column and max color value from the file.
    getImage>>r>>c>>m_c;
    destination_object.setRow(r);
    destination_object.setColumn(c);
    destination_object.setMaxColor(m_c);

    // If any of the readen values are below 0, throw some error.
    if(r < 0 || c < 0 || m_c < 0)
    {
        return FAIL; // INVALID_IMAGE_HEADER
    }

    // Allocating image space dynamically.
    destination_object.allocateImage();

    // Changing file name of the object to source file name.
    destination_object.setFileName(source_ppm_file_name);

    // Reading the Red, Green, Blue values from the file and filling up the image object with it.
    int columns = destination_object.getColumn();
    int rows = destination_object.getRow();
    for(int a = 0 ; a < columns ; a++ )
    {
        for(int b = 0 ; b < rows ; b++ )
        {
            for(int x = 0 ; x < 3 ; x++ )
            {
                getImage>>readen_color;
                destination_object(b, a, x+1) = readen_color;
            }
        }
    }
    getImage.close();
    return SUCCES;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object) 
{
    // If no image loaded yet, throw error.
    if(source_object.getImage() == NULL)
    {
        return FAIL; //NO_IMAGE_LOADED
    }

    // If cant create the image file, throw some error.
    ofstream setImage(destination_ppm_file_name);
    if(setImage.fail())
    {   
        setImage.close();
        return FAIL; // CANT_CREATE_IMAGE
    }
    // After creating succesfully, begin to write header of the image.
    setImage<<source_object.getFormat()<<endl;
    setImage<<source_object.getRow()<<" "<<source_object.getColumn()<<endl;
    setImage<<source_object.getMaxColor()<<endl;
    // Lastly, write the rgb values to the file.
    int rows = source_object.getRow();
    int columns = source_object.getColumn();
    for(int a = 0 ; a < columns ; a++ )
    {
        for(int b = 0 ; b < rows ; b++ )
        {
            setImage<<
            source_object(b, a, 1)<<" "<<source_object(b, a, 2)<<" "<<source_object(b, a, 3)<<
            " \t";  
        }
            setImage<<endl;
    }
    setImage.close();
    return SUCCES;
}




int test_addition(const string filename_image1, const string filename_image2, const string filename_image3) 
{
    ppmImage T1, T2, T3;
    if(read_ppm(filename_image1, T1) && read_ppm(filename_image2, T2))
    {
        T3 = T1 + T2;
        if(write_ppm(filename_image3, T3))
        {
            return SUCCES;
        }
        else
        {
            return FAIL;
        }
    }
    else
    {
        return FAIL;
    }
}



int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3) 
{
    ppmImage T1, T2, T3;
    if(read_ppm(filename_image1, T1) && read_ppm(filename_image2, T2))
    {
        T3 = T1 - T2;
        if(write_ppm(filename_image3, T3))
        {
            return SUCCES;
        }
        else
        {
            return FAIL;
        }
    }
    else
    {
        return FAIL;
    }
}



int test_print(const string filename_image1) 
{
    ppmImage T1;
    if(read_ppm(filename_image1, T1))
    {
        cout<<T1;
        return SUCCES;
    }
    else
    {
        return FAIL;
    }
}



int swap_channels(ppmImage&  image_object_to_be_modified, int swap_choice) 
{
    // If no image loaded yet, throw error.
    if(image_object_to_be_modified.getImage() == NULL)
    {
        return FAIL; //NO_IMAGE_LOADED
    }

    if(swap_choice > 0 && swap_choice < 4)
    {
        int rows = image_object_to_be_modified.getRow();
        int columns = image_object_to_be_modified.getRow();
        int temp;
        for(int a = 0 ; a < columns ; a++ )
        {
            for(int b = 0 ; b < rows ; b++ )
            {
                // using temp variable to store the copy, swapping color channels according to swap choice.
                switch(swap_choice)
                {
                    case 1:
                        temp = image_object_to_be_modified(b, a, 1);
                        image_object_to_be_modified(b, a, 1) = image_object_to_be_modified(b, a, 2);
                        image_object_to_be_modified(b, a, 2) = temp;
                        break;
                    case 2:
                        temp = image_object_to_be_modified(b, a, 1);
                        image_object_to_be_modified(b, a, 1) = image_object_to_be_modified(b, a, 3);
                        image_object_to_be_modified(b, a, 3) = temp;
                        break;
                    case 3:
                        temp = image_object_to_be_modified(b, a, 2);
                        image_object_to_be_modified(b, a, 2) = image_object_to_be_modified(b, a, 3);
                        image_object_to_be_modified(b, a, 3) = temp;
                        break;
                }
            }
        }
    }
    else
    {
        // do nothing here
    }
    return SUCCES;
}



ppmImage single_color(const ppmImage& source, int color_choice) {
    

    // If no image loaded yet, throw error.
    if(source.getImage() == NULL)
    {
        ppmImage empty_image;   
        return empty_image; //NO_IMAGE_LOADED
    }


    int rows = source.getRow();
    int columns = source.getColumn();
    ppmImage sc_image(rows, columns);
    for(int a = 0 ; a < columns ; a++ )
    {
        for(int b = 0 ; b < rows ; b++ )
        {
            switch(color_choice)
            {
                case 1:
                    // just copy the red value
                    sc_image(b, a, 1) = source(b, a, 1);
                    sc_image(b, a, 2) = 0;
                    sc_image(b, a, 3) = 0;
                    break;
                case 2:
                    // just copy the green value
                    sc_image(b, a, 1) = 0;
                    sc_image(b, a, 2) = source(b, a, 2);
                    sc_image(b, a, 3) = 0;
                    break;
                case 3:
                    // just copy the blue value
                    sc_image(b, a, 1) = 0;
                    sc_image(b, a, 2) = 0;
                    sc_image(b, a, 3) = source(b, a, 3);
                    break;
            }
        }
    }
    return sc_image;
}



/* STANDALONE FUNCTIONS END */



int main(int argc, char ** argv) {


    // If there's not enough arguments has passed, exit.
    if(argc < 2)
    {
        std::cout<<endl<<"Not enough information, please enter necessary arguments."<<endl;
        return 0;
    }


    string choice_string(argv[1]);
    string ppm_image_file[3] = {"", "", ""};


    // Getting image file names to the string array.
    for(int i = 2 ; i < argc ; i++)
    {
        ppm_image_file[i-2] = argv[i];
    }


    // Checking the choice_number for any invalid input.
    for(int i = 0 ; i < choice_string.size() ; i++)
    {
        if(choice_string[i] > '9' || choice_string[i] < '0')
        {
            cout<<endl<<"Choice number is invalid, please try again."<<endl;
            return 0;
        }
    }

    // Turn choice string to int.
    int choice = stoi(choice_string);

    /* There's a if at every case's start for checking if enough file name has entered or not. */
    switch(choice)
    {
        case 1:
        {
            if(ppm_image_file[0] != "" && ppm_image_file[1] != "" && ppm_image_file[2] != "")
            {
                test_addition(ppm_image_file[0], ppm_image_file[1], ppm_image_file[2]);
            }
            else 
            {
                cout<<endl<<"Not enough file name has entered, please enter at least 3 file name for addition."<<endl;
            }
            break;
        }
        case 2:
        {
            if(ppm_image_file[0] != "" && ppm_image_file[1] != "" && ppm_image_file[2] != "")
            {
                test_subtraction(ppm_image_file[0], ppm_image_file[1], ppm_image_file[2]);
            }
            else 
            {
                cout<<endl<<"Not enough file name has entered, please enter at least 3 file name for subtraction."<<endl;
            }
            break;
        }
        case 3:
        {
            if(ppm_image_file[0] != "" && ppm_image_file[1] != "")
            {
                ppmImage T1;
                read_ppm(ppm_image_file[0], T1);
                swap_channels(T1, 2);
                write_ppm(ppm_image_file[1], T1);
            }
            else 
            {
                cout<<endl<<"Not enough file name has entered, please enter at least 2 file name for swapping channels."<<endl;
            }
            break;
        }
        case 4:
        {
            if(ppm_image_file[0] != "" && ppm_image_file[1] != "")
            {
                ppmImage T1;
                read_ppm(ppm_image_file[0], T1);
                swap_channels(T1, 3);
                write_ppm(ppm_image_file[1], T1);
            }
            else 
            {
                cout<<endl<<"Not enough file name has entered, please enter at least 2 file name for swapping channels."<<endl;
            }
            break;
        }
        case 5:
        {
            if(ppm_image_file[0] != "" && ppm_image_file[1] != "")
            {
                ppmImage T1, T2;
                read_ppm(ppm_image_file[0], T1);
                T2 = single_color(T1, 1);
                write_ppm(ppm_image_file[1], T2);
            }
            else 
            {
                cout<<endl<<"Not enough file name has entered, please enter at least 2 file name for single color."<<endl;
            }
            break;
        }
        case 6:
        {
            if(ppm_image_file[0] != "" && ppm_image_file[1] != "")
            {
                ppmImage T1, T2;
                read_ppm(ppm_image_file[0], T1);
                T2 = single_color(T1, 2);
                write_ppm(ppm_image_file[1], T2);
            }
            else 
            {
                cout<<endl<<"Not enough file name has entered, please enter at least 2 file name for single color."<<endl;
            }
            break;
        }
        case 7:
        {
            if(ppm_image_file[0] != "" && ppm_image_file[1] != "")
            {
                ppmImage T1, T2;
                read_ppm(ppm_image_file[0], T1);
                T2 = single_color(T1, 3);
                write_ppm(ppm_image_file[1], T2);
            }
            else 
            {
                cout<<endl<<"Not enough file name has entered, please enter at least 2 file name for single color."<<endl;
            }
            break;
        }
    }
    
    return 1;
   
}


/* There's member functions to read and write from/to file but didnt used in main. */

int ppmImage::ppmsaveImageData() 
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


int ppmImage::openImage()
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
    allocateImage();


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


