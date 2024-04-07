#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void permute(short min_len, short max_len, vector<short>& nums, vector<short>& chosen, vector<vector<short>>& valid_moves, fstream& output_file) {
    if( chosen.size() >= min_len && chosen.size() <= max_len) {
        for(auto x : chosen) {
            output_file << x << ' ';
        }
        output_file << '\n';
    }

    if(chosen.size() == max_len) {
        return;
    } 

    for(int i=0; i<nums.size(); i++) {

        bool cont = false;
        for(int j=0; j<chosen.size(); j++) {
            if ( chosen[j] == nums[i] ) {
                cont = true;
                break;
            }
        }
        if(cont) continue;

        if( chosen.size() > 0 ) {
            bool is_valid_pos = false;
            for(auto valid=valid_moves.begin(); valid!=valid_moves.end(); valid++) {
                vector<short> next_position = { chosen.back(), nums[i] };
                if( next_position == *valid ) {
                    is_valid_pos = true;
                    break;
                }
            }

            if(is_valid_pos) {
                chosen.push_back( nums[i] );
                permute(min_len, max_len, nums, chosen, valid_moves, output_file);
                chosen.pop_back();  
            }
        } else {
            chosen.push_back( nums[i] );
            permute(min_len, max_len, nums, chosen, valid_moves, output_file);
            chosen.pop_back();  
        }

    }
}

void permutation(short min_len, short max_len, vector<short> nums, vector<vector<short>>& valid_moves, fstream& output_file) {
    vector<short> chosen;
    permute(min_len, max_len, nums, chosen, valid_moves, output_file);
}

void gen_valid_moves(vector<vector<short>>& valid_moves) {
    vector<vector<short>> grid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    vector<vector<short>> positions = {
        {-1, 1},
        {0, 1},
        {1, 1},
        {-1, 0},
        {1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
    };

    for(int x=0; x<grid.size(); x++) {
        for(int y=0; y<grid[0].size(); y++) {
            for(auto pos=positions.begin(); pos!=positions.end(); pos++) {
                short nextX_pos = x + (*pos)[0];
                short nextY_pos = y + (*pos)[1];

                if( nextX_pos >= 0 && nextX_pos < 4 && nextY_pos >= 0 && nextY_pos < 4 ) {
                    valid_moves.push_back({
                        grid[x][y], 
                        grid[nextX_pos][nextY_pos]
                    });
                }
            }
        }
    }
}

int main() {
    fstream valid_positions;
    valid_positions.open( OUTPUT_DIR + "valid_positions.txt"s , ios::out);
    if(!valid_positions.is_open()) {
        cerr << "Error opening new file." << endl;
        return -1;
    }

    vector<vector<short>> valid_moves;
    gen_valid_moves(valid_moves);

    vector<short> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 14, 15, 16};
    vector<vector<short>> result;
    short min_len = 1;
    short max_len = 8;

    permutation(min_len, max_len, nums, valid_moves, valid_positions);

    valid_positions.close();
}