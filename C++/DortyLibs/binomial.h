uint64_t binomial(int8_t n, int8_t k){
    uint64_t ans = 1;
    if (k > n-k)
        k = n-k;
    for(int8_t i = 0; i<k;i++){
        ans *= n-i;
        ans /= i+1;
    }
    return ans;
}



