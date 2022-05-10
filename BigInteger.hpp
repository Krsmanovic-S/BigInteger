#pragma once

#include <iostream>
#include <string>
#include <algorithm>

namespace BigInteger {
    using namespace std;

    // Function that adds two strings together.
    string add(string a, string b) {
        if(a == "0") return b;
        if(b == "0") return a;
        
        int i = a.size() - 1, j = b.size() - 1;
        unsigned char carry = 0, sum;
        string result = "";
        
        while(i >= 0 || j >= 0 || carry)
        {
            sum = 0;
            if(i >= 0) 
            {
                sum += (a[i] - '0'); 
                i--;
            }
            if(j >= 0) 
            {
                sum += (b[j] - '0'); 
                j--;
            }
            
            sum += carry;
            carry = sum / 10;
            result += to_string(sum % 10);
        }
        
        reverse(result.begin(),result.end());
        return result;   
    }

    // Helper Function that will perform one cycle of multiplication.
    // Shouldn't be called on individually, rather through multiply().
    string times(string num1, char digit) {
        unsigned char carry = 0, sum;
        string result = "";

        for(int i = num1.length() - 1; i >= 0; i--)
        {
            sum = int(num1[i] - '0') * (digit - '0') + carry;
            result = to_string(sum % 10) + result;
            carry = sum / 10;                
        }

        if(carry)
            result = to_string(carry) + result;
        return result;
    }

    // Main function that is called for multiplication.
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0" ) return "0";
        if(num1 == "1" ) return num2;
        if(num2 == "1" ) return num1;

        if(num1.length() < num2.length())
            swap(num1, num2);

        string result = "", x, temp;

        // Loop through the shorter string and call the
        // appropriate functions.
        for(int i = 0; i < num2.length(); i++)
        {
            // Add zeroes to the end of num1 depending on what i is.
            temp = num1 + string(i, '0');

            x = times(temp, num2[num2.length() - 1 - i]);
            result = add(result, x);                
        }

        return result[0] == '0' ? "0" : result;
    }

    // Function that divides a large number represented as a string. 
    string divide(string number, int divisor) {
        if(divisor == 0)
            throw runtime_error("Attempted to divide by Zero.\n");

        string result;

        // Find prefix of number that is larger than divisor.
        int index = 0, temp = number[index] - '0';
        while(temp < divisor)
            temp = temp * 10 + (number[++index] - '0');

        // Repeatedly divide divisor with temp. 
        while(number.size() > index) 
        {
            result += (temp / divisor) + '0';
    
            // Update temp to hold one more digit.
            temp = (temp % divisor) * 10 + number[++index] - '0';
        }

        return result.length() > 0 ? result : "0";            
    }
}