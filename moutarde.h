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
