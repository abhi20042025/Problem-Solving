class Solution {
public:
    static string lexGreaterPermutation(string& s, string& target) {
        const int n=s.size();
        array<int, 26> freq={0}, freq0;
        unsigned hasC=0, hasC0;
        for (char c : s) {
            const int idx=c-'a';
            if (++freq[idx]==1)
                hasC|=(1u<<idx);
        }

        int diffPos=-1;
        freq0=freq, hasC0=hasC;
        for (int i=0; i<n; i++) {
            int largestC=31-countl_zero(hasC0);
            int idx=target[i]-'a';
            if (largestC < idx) break;
            if (largestC > idx) diffPos=i;
            if (freq0[idx]>0) {
                if (--freq0[idx]==0) hasC0 &=~(1u<<idx);
            } 
            else break;
        }
    //    cout<<diffPos<<endl;
        if (diffPos==-1) return "";

        // rebuild s up to diffPos
        for (int j=0; j<diffPos; j++) {
            int idx=target[j]-'a';
            s[j]=target[j];
            if (--freq[idx]==0) hasC &=~(1u<<idx);
        }

        // increase at diffPos
        int shift=target[diffPos]-'a'+1;
        unsigned higher=hasC>>shift;
        if (higher==0) return "";
        int idx=countr_zero(higher)+shift;
        s[diffPos]='a'+idx;
        if (--freq[idx]==0) hasC&=~(1u<<idx); 

        // fill remaining with smallest
        for (int j=diffPos+1; j<n; j++) {
            idx=countr_zero(hasC);
            if (!hasC) return "";
            s[j]='a'+idx;
            if (--freq[idx]==0) hasC&=~(1u<<idx);
        }

        return s;
    }
};