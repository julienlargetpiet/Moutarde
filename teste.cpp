#include "moutarde.h"
#include <unistd.h>

void moutardify(std::string &moutarde, std::string &instruct_file, std::string &out_file, unsigned int end_head) {
  std::fstream moutarde_f(moutarde);
  std::string moutarde_str = "";
  std::string instruct_str = "";
  std::fstream instruct_f(instruct_file);
  std::fstream out_f(out_file, std::ios::out);
  std::string currow;
  std::string cur_data = "";
  std::vector<bool> history_sort = {};
  std::vector<bool> history_sort_ascending = {};
  std::vector<char> tracks_instructions = {};
  bool is_good_when;
  bool is_greater;
  std::vector<bool> alrd_found_whenv = {0};
  bool alrd_found_when;
  bool alrd_found_when2;
  unsigned int pre_len;
  unsigned int end_for_cnt;
  unsigned int post_len;
  unsigned int cur_pair;
  unsigned int cnt = 0;
  unsigned int cnt2 = 0;
  unsigned int depth_for = 0;
  std::vector<unsigned int> moutarde_cntv = {0};
  std::vector<unsigned int> moutarde_nextv = {};
  std::vector<unsigned int> ref_for_idxv = {};
  std::vector<unsigned int> ref_for_idxv2 = {};
  std::vector<unsigned int> len_v = {0};
  unsigned int moutarde_cnt = 0;
  unsigned int moutarde_cnt2;
  unsigned int next_idx;
  unsigned int path_level = 0;
  unsigned int ref_path_level = 0;
  unsigned int hmn_level;
  unsigned int tmp_cnt;
  int tmp_cnt2;
  unsigned int tmp_cnt3;
  char cur_instruction;
  char when_condition;
  std::vector<std::string> when_vec_args;
  std::vector<unsigned int> moutarde_pair_v;
  std::vector<unsigned int> moutarde_idx_v;
  std::vector<unsigned int> instruct_pair_v;
  std::vector<unsigned int> instruct_idx_v;
  std::vector<std::vector<unsigned int>> rtn_matr;
  std::vector<std::string> cur_pathv = {};
  std::vector<std::string> pre_sorted_data;
  end_head += 1;
  std::string cur_value;
  while (getline(moutarde_f, currow)) {
    moutarde_str += currow;
    moutarde_str.push_back('\n');
  };
  while (getline(instruct_f, currow)) {
    cnt += 1;
    if (cnt == end_head) {
      break;
    };
  };
  while (getline(instruct_f, currow)) {
    instruct_str += currow;
    instruct_str.push_back('\n');
  };
  rtn_matr = Parser_tokenizer_full(moutarde_str);
  moutarde_pair_v = rtn_matr[0];
  moutarde_idx_v = rtn_matr[1];
  rtn_matr = Parser_tokenizer_full(instruct_str);
  instruct_pair_v = rtn_matr[0];
  instruct_idx_v = rtn_matr[1];
  cnt = 1;
  cnt2 = 1;
  const unsigned int n = instruct_str.length();
  const unsigned int n_token = instruct_idx_v.size(); 
  const unsigned int n2 = moutarde_str.length();
  const unsigned int n2_token = moutarde_idx_v.size();
  while (cnt < n_token) {
    next_idx = instruct_idx_v[cnt];
    while (cnt2 < next_idx) {
      cur_data.push_back(instruct_str[cnt2]);
      cnt2 += 1;
    };
    if (instruct_str[next_idx] == '(') {
      cur_instruction = instruct_str[next_idx + 1];
      tracks_instructions.push_back(cur_instruction);
      cur_value = "";
      cnt2 += 3;
      while (instruct_str[cnt2] != ':') {
        if (instruct_str[cnt2] != '/') {
          cur_value.push_back(instruct_str[cnt2]);
        } else {
          cur_pathv.push_back(cur_value);
          cur_value = "";
        };
        cnt2 += 1;
      };
      cur_pathv.push_back(cur_value);
      len_v.push_back(cur_pathv.size());
      cnt2 += 1;
      if (cur_instruction == 'w') {
        cur_value = "";
        when_vec_args = {};
        when_condition = instruct_str[cnt2];
        cnt2 += 2;
        while (instruct_str[cnt2] != ']') {
          if (instruct_str[cnt2] != ',') {
            cur_value.push_back(instruct_str[cnt2]);
          } else {
            when_vec_args.push_back(cur_value);
            cur_value = "";
          };
          cnt2 += 1;
        };
        cnt2 += 1;
        when_vec_args.push_back(cur_value);
      } else if (cur_instruction == 'f') {
        cur_pair = instruct_pair_v[cnt];
        tmp_cnt = cnt + 1;
        while (instruct_pair_v[tmp_cnt] != cur_pair) {
          tmp_cnt += 1;
        };
        end_for_cnt = tmp_cnt;
        depth_for += 1;
        while (moutarde_cnt + 1 < n2_token & path_level >= ref_path_level) {
          if (moutarde_str[moutarde_idx_v[moutarde_cnt]] == '(') {
            moutarde_cnt2 = moutarde_idx_v[moutarde_cnt] + 1;
            cur_value = "";
            while (moutarde_str[moutarde_cnt2] != ':') {
              cur_value.push_back(moutarde_str[moutarde_cnt2]);
              moutarde_cnt2 += 1;
            };
            if (cur_value == cur_pathv[path_level]) {
              if (path_level + 1 == cur_pathv.size()) {
                ref_path_level = path_level;
                moutarde_cntv.push_back(moutarde_cnt);
                cur_pair = moutarde_pair_v[moutarde_cnt];
                tmp_cnt = moutarde_cnt + 1;
                while (cur_pair != moutarde_pair_v[tmp_cnt]) {
                  tmp_cnt += 1;
                };
                moutarde_nextv.push_back(tmp_cnt + 1);
                ref_for_idxv.push_back(cnt);
                ref_for_idxv2.push_back(instruct_idx_v[cnt]);
                alrd_found_whenv.push_back(0);
                break;
              };
              path_level += 1;
            } else {
              cur_pair = moutarde_pair_v[moutarde_cnt];
              tmp_cnt = moutarde_cnt + 1;
              while (cur_pair != moutarde_pair_v[tmp_cnt]) {
                tmp_cnt += 1;
              };
              moutarde_cnt = tmp_cnt;
            };
          } else {
            path_level -= 1;
          };
          moutarde_cnt += 1;
        };
        if (moutarde_cnt + 1 >= n2_token || path_level < ref_path_level) {
          cnt = end_for_cnt;
          cnt2 = instruct_idx_v[end_for_cnt] + 1;
          tracks_instructions.pop_back();
          cur_instruction = '?';
          depth_for -= 1;
          pre_len = len_v[len_v.size() - 2];
          post_len = len_v[len_v.size() - 1];
          for (tmp_cnt = pre_len; tmp_cnt < post_len; ++tmp_cnt) {
            cur_pathv.pop_back();
            ref_path_level -= 1;
          };
          len_v.pop_back();
          path_level = ref_path_level;
          moutarde_cnt = moutarde_cntv[depth_for];
        };
      };
      if (cur_instruction == 'v' || cur_instruction == 'w') {
        hmn_level = cur_pathv.size() - 1;
        path_level = ref_path_level;
        moutarde_cnt = moutarde_cntv[depth_for];
        cur_pair = instruct_pair_v[cnt];
        while (moutarde_cnt + 1 < n2_token & path_level >= ref_path_level) {
          if (moutarde_str[moutarde_idx_v[moutarde_cnt]] == '(') {
            moutarde_cnt2 = moutarde_idx_v[moutarde_cnt] + 1;
            cur_value = "";
            while (moutarde_str[moutarde_cnt2] != ':') {
              cur_value.push_back(moutarde_str[moutarde_cnt2]);
              moutarde_cnt2 += 1;
            };
            if (cur_pathv[path_level] == cur_value) {
              if (path_level < hmn_level) {
                moutarde_cnt += 1;
              } else {
                alrd_found_whenv[depth_for] = 1;
                if (cur_instruction == 'v') {
                  moutarde_cnt2 += 1;
                  while (moutarde_str[moutarde_cnt2] != ')') {
                    cur_data.push_back(moutarde_str[moutarde_cnt2]);
                    moutarde_cnt2 += 1;
                  };
                  break;
                } else {
                  moutarde_cnt2 += 1;
                  cur_value = "";
                  while (moutarde_str[moutarde_cnt2] != ')') {
                    cur_value.push_back(moutarde_str[moutarde_cnt2]);
                    moutarde_cnt2 += 1;
                  };
                  is_good_when = 0;
                  if (when_condition == '=') {
                    for (tmp_cnt = 0; tmp_cnt < when_vec_args[when_vec_args.size() - 1].size(); ++tmp_cnt) {
                      if (when_vec_args[tmp_cnt] == cur_value) {
                        is_good_when = 1;
                        break;
                      };
                    };
                  } else if (when_condition == '!') {
                    for (tmp_cnt = 0; tmp_cnt < when_vec_args[when_vec_args.size() - 1].size(); ++tmp_cnt) {
                      if (when_vec_args[tmp_cnt] != cur_value) {
                        is_good_when = 1;
                        break;
                      };
                    };
                  } else if (when_condition == '>') {
                    for (tmp_cnt = 0; tmp_cnt < when_vec_args[when_vec_args.size() - 1].size(); ++tmp_cnt) {
                      is_greater = is_greater_str(cur_value, when_vec_args[tmp_cnt]);
                      if (is_greater) {
                        is_good_when = 1;
                        break;
                      };
                    };
                  } else if (when_condition == '<') {
                    for (tmp_cnt = 0; tmp_cnt < when_vec_args[when_vec_args.size() - 1].size(); ++tmp_cnt) {
                      is_greater = is_greater_str(cur_value, when_vec_args[tmp_cnt]);
                      if (!is_greater) {
                        is_good_when = 1;
                        break;
                      };
                    };
                  };
                  if (is_good_when) {
                    pre_len = len_v[len_v.size() - 2];
                    post_len = len_v[len_v.size() - 1];
                    for (tmp_cnt = pre_len; tmp_cnt < post_len; ++tmp_cnt) {
                      cur_pathv.pop_back();
                    };
                    len_v.pop_back();
                    tmp_cnt = moutarde_cnt + 2;
                    tmp_cnt3 = 0;
                    while (tmp_cnt3 < (path_level - ref_path_level)) {
                      alrd_found_when2 = 0;
                      while (!alrd_found_when2) {
                        tmp_cnt2 = moutarde_cnt - 1;
                        while (tmp_cnt2 >= 0) {
                          if (moutarde_pair_v[tmp_cnt] == moutarde_pair_v[tmp_cnt2]) {
                            alrd_found_when2 = 1;
                            break;
                          };
                          tmp_cnt2 -= 1;
                        };
                        tmp_cnt += 1;
                      };
                      tmp_cnt3 += 1;
                    };
                    moutarde_cntv[depth_for] = tmp_cnt2;
                    moutarde_nextv[depth_for - 1] = tmp_cnt;
                    moutarde_cnt = tmp_cnt2;
                    path_level = ref_path_level;
                    break;
                  } else {
                    moutarde_cnt += 1;
                  };
                };
              };
              path_level += 1;
            } else {
              cur_pair = moutarde_pair_v[moutarde_cnt];
              moutarde_cnt += 1;
              while (cur_pair != moutarde_pair_v[moutarde_cnt]) {
                moutarde_cnt += 1;
              };
              moutarde_cnt += 1;
            };
          } else{
            path_level -= 1;
            moutarde_cnt += 1;
          };
        };
        if (moutarde_cnt  + 1 == n2_token || path_level < ref_path_level) {
          if (cur_instruction == 'w') {
            alrd_found_when = alrd_found_whenv[depth_for];
            if (!alrd_found_when) {
              std::cout << "(WHERE ERROR) for path: \n";
              tmp_cnt = 0;
              while (tmp_cnt < cur_pathv.size() - 1) {
                std::cout << cur_pathv[tmp_cnt] << "/";
                tmp_cnt += 1;
              };
              std::cout << cur_pathv[tmp_cnt];
              std::cout << "\n";
              return;
            } else {
              pre_len = len_v[len_v.size() - 2];
              post_len = len_v[len_v.size() - 1];
              for (tmp_cnt = pre_len; tmp_cnt < post_len; ++tmp_cnt) {
                cur_pathv.pop_back();
              };
              len_v.pop_back();
              cnt += 1;
              while (cur_pair != instruct_pair_v[cnt]) {
                cnt += 1;
              };
              cnt -= 1;
              cnt2 = instruct_idx_v[cnt + 1];
            };
          } else {
             std::cout << "(VALUE ERROR) for path: \n";
             tmp_cnt = 0;
             while (tmp_cnt < cur_pathv.size() - 1) {
               std::cout << cur_pathv[tmp_cnt] << "/";
               tmp_cnt += 1;
             };
             std::cout << cur_pathv[tmp_cnt];
             std::cout << "\n";
            return;
          };
        };
      };
    } else {
      cnt2 = next_idx + 1;
      if (tracks_instructions.size() > 0) {
        cur_instruction = tracks_instructions[tracks_instructions.size() - 1];
        tracks_instructions.pop_back();
      };
      if (cur_instruction != 'w') {
        pre_len = len_v[len_v.size() - 2];
        post_len = len_v[len_v.size() - 1];
        for (tmp_cnt = pre_len; tmp_cnt < post_len; ++tmp_cnt) {
          cur_pathv.pop_back();
        }; 
        len_v.pop_back();
      };
      if (cur_instruction == 'f') {
        path_level = ref_path_level;
        cnt = ref_for_idxv[depth_for - 1] - 1;
        cnt2 = ref_for_idxv2[depth_for - 1] - 1;
        depth_for -= 1;
        moutarde_cnt = moutarde_nextv[depth_for];
        moutarde_nextv.pop_back();
        moutarde_cntv.pop_back();
        ref_for_idxv.pop_back();
        ref_for_idxv2.pop_back();
        alrd_found_whenv.pop_back();
      };
    };
    cnt += 1;
  };
  std::cout << cur_data << "\n";
};

int main() {
 
  std::string instruct_file = "teste.instruct";
  std::string moutarde_file = "teste.moutarde";
  std::string html_file = "teste.html";
  unsigned int end_head = 6;

  moutardify(moutarde_file, instruct_file, html_file, end_head);

  return 0;
};


