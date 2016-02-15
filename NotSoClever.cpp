#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool IsDigit(string charIter)
{
    bool isDigit = false;

    if(charIter[0] >= 49 && charIter[0] <= 56)
    {
        isDigit = true;
    }
    else
    {
        isDigit = false;
        cout << "Number of iterations not valid" << endl;
    }

    return isDigit;
}

bool ParseLine(string& vals, int& iterations, string line)
{
    bool retVal = false;

    string iters;

    size_t delPos = line.find("|");

    if(delPos == string::npos)
    {
        retVal = false;

        cout << "| character not found in input string" << endl;
    }
    else
    {
        vals = line.substr(0,delPos-1);
        iters = line.substr(delPos+2, (line.size()-delPos-1));

        //cout << "Data: " << vals << endl;
        //cout << "Data Size: " << vals.size() << endl;
        //cout << "Iterations: " << iters << endl;
        //cout << "Iterations size: " << iters << endl;

        if(IsDigit(iters) == true)
        {
            iterations = iters[0] - 48;

            retVal = true;
        }
    }

    return retVal;
}

void ParseData(vector<int> &nums, string data)
{
    unsigned int index = 0;

    int result;

    stringstream dataStream(data);
    string temp;

    while(getline(dataStream,temp,' '))
    {
        istringstream stringResult(temp);

        stringResult >> result;

        nums.push_back(result);

        ++index;
    }
}

void NotSoCleverSort(vector<int> &nums, const int iterations)
{
    unsigned int index = 0;
    int iterationsIndex = 0;

    bool swap = false;

    while((index < nums.size()-1) && (iterationsIndex < iterations))
    {
        if(nums[index] > nums[index+1])
        {
            int temp = nums[index];
            nums[index] = nums[index+1];
            nums[index+1] = temp;
            ++iterationsIndex;
            swap = true;
        }

        if(swap == true)
        {
            index = 0;
            swap = false;
        }
        else
        {
            ++index;
        }
    }
}

int main(int argc, char *argv[])
{
    ifstream inputFile;
    
    string line;

    inputFile.open(argv[1]);

    if(inputFile.is_open())
    {
        while(getline(inputFile,line))
        {
            string vals;
            int iterations = 0;
            bool lineParsed;

            lineParsed = ParseLine(vals, iterations, line);

            if(lineParsed)
            {
                vector<int> nums;

                ParseData(nums, vals);

                NotSoCleverSort(nums,iterations);

                unsigned int index = 0;

                for(vector<int>::iterator it = nums.begin();
                    it != nums.end();
                    ++it)
                {
                    if(index != nums.size()-1)
                    {
                        cout << *it << " ";
                    }
                    else
                    {
                        cout << *it << endl;
                    }
                    ++index;
                }

                //cout << line << endl;
            }
        }
    }
    else
    {
        cout << "Error opening input file" << endl;
    }

    inputFile.close();

    return 0;
}
