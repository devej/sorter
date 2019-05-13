#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>


class InputFileLoader
{
public:
    InputFileLoader() = delete;

    explicit InputFileLoader( const std::string & filename )
    {
        auto trim_right = [] ( std::string& s )
        {
            s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !std::isspace(ch);
            }).base(), s.end());
        };

        std::string line;
        std::ifstream infile( filename );

        if( !infile.is_open() ) {
            std::ostringstream oss;
            oss << "ERROR opening :" << filename << std::endl;
            throw oss.str();
        }

        while( std::getline(infile, line) )
        {
            trim_right( line );
            if( !line.empty() )
                _numbers.emplace_back( std::atol( line.c_str() ) );
        }
    }

    const std::vector<int64_t>& getData() const { return _numbers; }

private:
    std::vector< int64_t > _numbers;
};


void sort( const std::vector<int64_t>& vec )
{
    // Count up the frequencies
    std::map< int64_t, int64_t > frequencies;
    for( auto& i : vec ) {
        ++frequencies[i];
    }

    using T = std::pair< int64_t, int64_t >;

    // The sorting logic
    auto cmp = []( const T& lhs, const T& rhs )
    {
        if( lhs.second < rhs.second )
            return true;
        else if( lhs.second == rhs.second )
            return lhs.first < rhs.first;
        else
            return false;
    };

    std::set< T, decltype(cmp) > sorted(cmp);

    // Move the value/frequency pairs to the sorting set.
    // Beware: the map's values are trash afterwards.
    for( auto& pr: frequencies ) {
        sorted.emplace( std::move(pr) );
    }

    // Print the sorted set.
    // Since we didn't copy all the actual values, print each value "frequency" times
    for( auto& [num, freq] : sorted )
    {
        for( int x=0; x < freq; ++x )
            std::cout << num << std::endl;
    }
}


void usage()
{
    std::cout << "usage: sorter <filename>" << std::endl
        << "\tWhere <filename> names a file with numbers in a single column." << std::endl;
}


int main( int argc, char** argv )
{
    if( argc == 2 )
    {
        try {
            const std::string filename( argv[1] );
            InputFileLoader ifl( filename );
            sort( ifl.getData() );
        }
        catch( const std::exception& e ) {
            std::cout << "Unexpected error: " << e.what() << std::endl;
            return 1;
        }
    }
    else
    {
        usage();
        return 1;
    }
    
    return 0;
}
