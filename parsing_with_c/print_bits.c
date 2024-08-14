void print_bits(char c){
    int i; 
    for(i=0; i<sizeof(char)*8; i++){
        if (/* condition */)
        {
            printf("1"); 
        }
        else {
            printf("0"); 
        }
        
    }
    printf("\n"); 
}