#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::vector<unsigned int>> Parser_tokenizer_full(std::string &x, char frst_chr = '(', char scd_chr = ')') {
  std::vector<unsigned int> num_par;
  std::vector<int> cur_val;
  std::vector<unsigned int> idx_vec;
  int i2;
  unsigned int cur_num = 0;
  const unsigned int n = x.length();
  bool alrd;
  for (int i = 0; i < n; ++i) {
    if (x[i] == frst_chr) {
      idx_vec.push_back(i);
      num_par.push_back(0);
      for (i2 = 0; i2 < cur_val.size(); ++i2) {
        cur_val[i2] += 1;
      };
      cur_val.push_back(1);
    } else if (x[i] == scd_chr) {
        idx_vec.push_back(i);
        i2 = cur_val.size() - 1;
        num_par.push_back(0);
        cur_val.push_back(1);
        alrd = 0;
        while (i2 > -1) {
          cur_val[i2] -= 1;
          if (cur_val[i2] == 0 & !alrd) {
            num_par[i2] = cur_num;
            num_par[num_par.size() - 1] = cur_num;
            cur_val[cur_val.size() - 1] = 0;
            cur_num += 1;
            alrd = 1;
          };
          i2 -= 1;
        };
    };
  };
  return {num_par, idx_vec};
};



template <typename T> void print_nvec(const std::vector<T> &x, int untl = -1) {
  unsigned int r = 1;
  int i;
  int cmax = 1;
  int cl;
  unsigned int Untl;
  if (untl == -1) {
    Untl = x.size();
  } else {
    Untl = untl;
  };
  for (i = 0; i < Untl; ++i) {
    cl = std::to_string(x[i]).length();
    if (cl > cmax) {
      cmax = cl;
    };
  }; 
  int ref_delta = std::to_string(Untl).length();
  for (i = 0; i < ref_delta - 1; ++i) {
    std::cout << " ";
  };
  std::cout << ":" << 0 << ": ";
  for (i = 0; i < Untl; ++i) {
    if ((i + 1) % 10 == 0) {
      std::cout << x[i] << " ";
      for (cl = 0; cl < cmax - std::to_string(x[i]).length(); ++cl) {
        std::cout << " ";
      };
      std::cout << "\n";
      for (cl = 0; cl < ref_delta - std::to_string(r * 10).length(); ++cl) {
        std::cout << " ";
      };
      std::cout << ":" << r * 10 << ": ";
      r += 1;
    } else {
      std::cout << x[i] << " ";
      for (cl = 0; cl < cmax - std::to_string(x[i]).length(); ++cl) {
        std::cout << " ";
      };
    };
  };
  std::cout << "\n";
};

template <typename T, typename T2> unsigned int match(const std::vector<T> &source, const T2 &ptrn) {
  int cnt = 0;
  for (typename std::vector<T>::const_iterator i = source.begin(); i != source.end(); ++i) {
    if (*i == ptrn) {
      return cnt;
    };
    cnt += 1;
  };
  return -1;
};

bool is_greater_str(std::string &x, std::string &x2) {
  std::vector<char> order_v = {
     ' ', '!', '"', '#', '$', '%', '&', 
     '\'', '(', ')', '*', '+', ',', '-', 
     '.', '/', ':', ';', '<', '=',
     '>', '?', '@', 'A', 'a', 'B', 'b', 'C', 'c',
     'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g', 'H', 
     'h', 'I', 'i', 'J', 'j', 'K', 'k', 'L', 'l', 
     'M', 'm', 'N', 'n', 'O', 'o', 'P', 'p', 'Q', 'q', 
     'R', 'r', 'S', 's', 'T', 't', 'U', 'u', 'V', 'v', 
     'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z', 
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
     '[', '\\', 
     ']', '^', '_', '`', '{', '|', '}',
     '~'};
  const unsigned int n = x.length();
  const unsigned int n2 = x2.length();
  unsigned int val1;
  unsigned int val2;
  if (n == n2) {
    for (unsigned int i = 0; i < n; ++i) {
      val1 = match(order_v, x[i]);
      val2 = match(order_v, x2[i]);
      if (val1 != val2) {
        if (val1 > val2) {
          return 1;
        } else {
          return 0;
        };
      };
    };
  } else if (n > n2) {
    return 1;
  } else {
    return 0;
  };
  return 1;
};

std::vector<std::string> str_sort_descend(std::vector<std::string> &x) {
  unsigned int i;
  unsigned int i2;
  const unsigned int n = x.size();
  std::vector<std::string> rtn_v = {};
  rtn_v.reserve(n);
  std::string cur_str;
  std::vector<std::string> x_ref = x;
  std::string min_str = " ";
  unsigned int max_len = 1;
  unsigned int cur_len;
  unsigned int idx_max;
  bool is_sup;
  for (i = 0; i < n; ++i) {
    cur_str = x[i];
    cur_len = cur_str.length();
    if (max_len < cur_len) {
      max_len = cur_len;
    };
  };
  for (i = 0; i < n; ++i) {
    cur_str = x[i];
    cur_len = cur_str.length();
    for (i2 = cur_len; i2 < max_len; ++i2) {
      cur_str.push_back(' ');
    };
    x[i] = cur_str;
  };
  for (i = 0; i < n; ++i) {
    cur_str = x[i];
    idx_max = i;
    for (i2 = 0; i2 < n; ++i2) {
      is_sup = is_greater_str(x[i2], cur_str);
      if (is_sup) {
        cur_str = x[i2];
        idx_max = i2;
      };
    };
    x[idx_max] = min_str;
    rtn_v.push_back(x_ref[idx_max]);
  };
  return rtn_v;
};

std::vector<std::string> str_sort_ascend(std::vector<std::string> x) {
  unsigned int i;
  unsigned int i2;
  const unsigned int n = x.size();
  std::vector<std::string> rtn_v = {};
  rtn_v.reserve(n);
  std::string cur_str;
  std::vector<std::string> x_ref = x;
  std::string max_str = "~";
  unsigned int max_len = 1;
  unsigned int cur_len;
  unsigned int idx_min;
  bool is_sup;
  for (i = 0; i < n; ++i) {
    cur_str = x[i];
    cur_len = cur_str.length();
    if (max_len < cur_len) {
      max_len = cur_len;
    };
  };
  for (i = 1; i < max_len; ++i) {
    max_str.push_back('~');
  };
  for (i = 0; i < n; ++i) {
    cur_str = x[i];
    cur_len = cur_str.length();
    for (i2 = cur_len; i2 < max_len; ++i2) {
      cur_str.push_back(' ');
    };
    x[i] = cur_str;
  };
  for (i = 0; i < n; ++i) {
    cur_str = x[i];
    idx_min = i;
    for (i2 = 0; i2 < n; ++i2) {
      is_sup = is_greater_str(x[i2], cur_str);
      if (!is_sup) {
        cur_str = x[i2];
        idx_min = i2;
      };
    };
    x[idx_min] = max_str;
    rtn_v.push_back(x_ref[idx_min]);
  };
  return rtn_v;
};

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
  unsigned int where_pair;
  unsigned int where_cnt;
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
    cur_data += currow;
    cur_data.push_back('\n');
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
        where_pair = instruct_pair_v[cnt];
        where_cnt = cnt;
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
                    for (tmp_cnt = 0; tmp_cnt < when_vec_args.size(); ++tmp_cnt) {
                      if (when_vec_args[tmp_cnt] == cur_value) {
                        is_good_when = 1;
                        break;
                      };
                    };
                  } else if (when_condition == '!') {
                    for (tmp_cnt = 0; tmp_cnt < when_vec_args.size(); ++tmp_cnt) {
                      if (when_vec_args[tmp_cnt] != cur_value) {
                        is_good_when = 1;
                        break;
                      };
                    };
                  } else if (when_condition == '>') {
                    for (tmp_cnt = 0; tmp_cnt < when_vec_args.size(); ++tmp_cnt) {
                      is_greater = is_greater_str(cur_value, when_vec_args[tmp_cnt]);
                      if (is_greater) {
                        is_good_when = 1;
                        break;
                      };
                    };
                  } else if (when_condition == '<') {
                    for (tmp_cnt = 0; tmp_cnt < when_vec_args.size(); ++tmp_cnt) {
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
              cnt = where_cnt + 1;
              while (where_pair != instruct_pair_v[cnt]) {
                cnt += 1;
              };
              cnt -= 1;
              cnt2 = instruct_idx_v[cnt + 1];
              path_level = ref_path_level;
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
  out_f << cur_data; 
};


