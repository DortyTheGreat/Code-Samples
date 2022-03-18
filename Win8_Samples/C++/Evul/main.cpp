#include <iostream>
#include <vector>
#include <queue>


#include <iostream>
#include <fstream>
#include <cstdlib>

#include <iostream>

#include <stdio.h>
#include <stdlib.h> // atoi

#include <io.h>
#include <fcntl.h>
#include <conio.h>

#include <ctype.h>

using namespace std;


bool evalXYZW( wstring expression )
{
    wstring program = L"";
    program = program + L"#include <cmath>\n";
    program = program + L"#include <iostream>\n";
    program = program + L"using namespace std;\n";
    program = program + L"int main()\n";
    program = program + L"{\n";
    program = program + L"cout << \"x y z w \" << endl;\n";
    program = program + L"for(int x = 0; x < 2; x++) \n";
    program = program + L"for(int y = 0; y < 2; y++) \n";
    program = program + L"for(int z = 0; z < 2; z++) \n";
    program = program + L"for(int w = 0; w < 2; w++) \n";
    program = program + L"if(" + expression + L")" +   L" cout << x << \" \" << y << \" \" << z << \" \" << w << endl; \n";
    program = program + L"}";


    wofstream out( "abc.cpp" );
    out << program;
    out.close();

    system( "g++ -o abc.exe abc.cpp" );
    system( "abc" );
}


bool Calcule( wstring str )
{

    wstring expression = str;
    wcout << L"Expression [ " << expression << L" ] = " << endl;
    return  evalXYZW( expression );

}

wstring NewReplace(wstring start, int what, wstring withwhat)
{
    wstring ans=L"";
    wstring a, b, c;
    int d = 0;
    a = start;
    for (int i = 0; i < a.length(); ++i){
        bool fl = 1;

        if ( (int)(a[i]) == what ){
        ans+= withwhat;
        }
        else{ ans += a[i];}
    }
    return ans;
}

int main(){
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin),  _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

wstring a;

wcout << (int)L'∧' << endl;
//wstring test; wcin >> test; wcout << (int)(test[0]);

getline(wcin,a);
a = NewReplace(a,172,L"!");
a = NewReplace(a,167,L"&&");
a = NewReplace(a,1025,L"||");
wcout << a << endl;

wcout << Calcule(a);

}
