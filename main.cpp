#include <iostream>


// Packet without footer, HDR_MARK < HDR_SPACE
uint16_t ir_data[] = {
                        31074, 
                        4567, 9345, 
                        572, 1691, 576, 1691, 570, 1691, 573, 560, 573, 560, 569, 560, 572, 559, 574, 1691,
                        568, 1697, 572, 559, 570, 558, 573, 1694, 573, 1689, 569, 1687, 572, 559, 574, 558
                    };


#define MIN_DATA_BITS       8
#define MIN_PACKET_SIZE     34        // Junk + HDR_MARK + HDR_SPACE + (DATA_BITS x 2) --> DATA_BITS = 16
uint16_t ERROR = 80;


typedef struct IR_VAL_HEX {
  unsigned long long int third;
  unsigned long long int second;
  unsigned long long int first;
  /* data */
} ir_val_hex_t;

typedef struct IR_DATA_PACKET
{
    uint8_t  bits[3];
    uint16_t hdr_mark;
    uint16_t hdr_space;
    uint16_t bit_mark;
    uint16_t one_space;
    uint16_t zero_space;
    uint16_t gap;
    uint16_t ftr_mark;
    uint16_t ftr_space;
    uint8_t	 repeat;
    uint8_t  flags;
    ir_val_hex_t decoded_val[3];
}ir_decoded_data_t;

enum ir_decode_flags
{
    FIRST_PACKET        =   1,
    SECOND_PACKET       =   2,
    THIRD_PACKET        =   3,
    UNIQUE_FOOTER       =   4,
    NEC_FOOTER          =   5,
    REPEAT              =   6
};

enum repeat_types
{
    NO_REPEAT           =   0,
    REPEAT_SINGLE       =   1,
    REPEAT_TWICE        =   2
};


void init_decode_data(ir_decoded_data_t *_ir_decoded_data);
void init_hex_data(ir_val_hex_t *_ir_hex_value);

void print_decode_data(ir_decoded_data_t *_ir_decoded_data);

void decode_packet(uint16_t pkt_start, uint16_t pkt_end, ir_decoded_data_t *_ir_decoded_data);
void decode_packet(uint16_t pkt_start, uint16_t pkt_end, uint16_t pkt_sequence, ir_decoded_data_t *_ir_decoded_data, bool final_pkt);

void set_flags(ir_decoded_data_t *_ir_decoded_data);
bool compare_hex_value(ir_val_hex_t _hex_value_a, ir_val_hex_t _hex_value_b, uint8_t _bit_count_a, uint8_t _bit_count_b);

void receive_ir_packet(uint32_t remote_id, uint8_t cmd, uint8_t communication_id);

void send_ir_can_message(ir_decoded_data_t ir_decoded_data, uint32_t *remote_id, uint8_t *cmd, uint8_t *communication_id);
void can_send_hex_value(ir_decoded_data_t _ir_decode_data, uint8_t *seq_no, uint8_t communication_id, uint8_t pkt_num);

int set_bit(int n, int k);
int clear_bit(int n, int k);
int toggle_bit(int n, int k);
int bit_get(int n, int k);


int main()
{
    uint32_t remote_id;
    uint8_t cmd;
    uint8_t communication_id;

    remote_id = 0x23AC09;
    cmd = 0x17;
    communication_id = 0x7A;

    receive_ir_packet(remote_id, cmd, communication_id);
    
    return 0;
}  


// Function to set the kth bit of n
int set_bit(int n, int k)
{
    return (n | (1 << (k - 1)));
}
  
// Function to clear the kth bit of n
int clear_bit(int n, int k)
{
    return (n & (~(1 << (k - 1))));
}
  
// Function to toggle the kth bit of n
int toggle_bit(int n, int k)
{
    return (n ^ (1 << (k - 1)));
}

// Function to read the kth bit of n
int bit_get(int n, int k)
{
    int x = (n >> (k - 1)) & 0x01;
    return x;
}

// Initialize ir_val_hex_t Struct
void init_hex_data(ir_val_hex_t *_ir_hex_value)
{
    _ir_hex_value->first  = 0x00;
    _ir_hex_value->second = 0x00;
    _ir_hex_value->third  = 0x00;
}

// Initialize ir_decoded_data_t Struct
void init_decode_data(ir_decoded_data_t *_ir_decoded_data)
{
    ir_val_hex_t hex_val_0;
    ir_val_hex_t hex_val_1;
    ir_val_hex_t hex_val_2;

    // initalize hex values
    init_hex_data(&hex_val_0);
    init_hex_data(&hex_val_1);
    init_hex_data(&hex_val_2);
    _ir_decoded_data->decoded_val[0] = hex_val_0;
    _ir_decoded_data->decoded_val[1] = hex_val_1;
    _ir_decoded_data->decoded_val[2] = hex_val_2;

    // initalize data bits
    for(uint8_t i = 0; i < 3; i++)
    {
        _ir_decoded_data->bits[i] = 0;
    }

    // initalize Header Mark/Space, One Mark/Space and Zero Mark/Space value
    _ir_decoded_data->hdr_mark = 0;
    _ir_decoded_data->hdr_space = 0;
    _ir_decoded_data->bit_mark = 0;
    _ir_decoded_data->one_space = 0;
    _ir_decoded_data->zero_space = 0;

    // initialize Gap, Footer, and Repeat Count
    _ir_decoded_data->gap = 0;
    _ir_decoded_data->ftr_mark = 0;
    _ir_decoded_data->ftr_space = 0;
    _ir_decoded_data->repeat = 0;

    // initialize Flags
    _ir_decoded_data->flags = 0;
}

// Compare two ir_val_hex_t Structs and return true/ false
bool compare_hex_value(ir_val_hex_t _hex_value_a, ir_val_hex_t _hex_value_b, uint8_t _bit_count_a, uint8_t _bit_count_b)
{
    bool result = false;

    if(_bit_count_a == _bit_count_b)
    {
        if(_bit_count_a > 128)
        {
            if((_hex_value_a.third == _hex_value_b.third) &&
                (_hex_value_a.second == _hex_value_b.second) &&
                (_hex_value_a.first == _hex_value_b.first))
            {
                result = true;
            }
            else
            {
                result = false;
            }
        }
        else if(_bit_count_a > 64)
        {
            if((_hex_value_a.second == _hex_value_b.second) &&
                (_hex_value_a.first == _hex_value_b.first))
            {
                result = true;
            }
            else
            {
                result = false;
            }
        }
        else if(_bit_count_a > 0)
        {
            if(_hex_value_a.first == _hex_value_b.first)
            {
                result = true;
            }
            else
            {
                result = false;
            }
        }
    }
    else
    {
        result = false;
    }

    return result;
}

// print decoded data
void print_decode_data(ir_decoded_data_t *_ir_decoded_data)
{
    printf("----------------------------------------------------------------------\n");

    printf("Data Flags \t\t: 0x%X\n", _ir_decoded_data->flags);
    printf("Header Mark \t\t: %d\n", _ir_decoded_data->hdr_mark);
    printf("Header Space \t\t: %d\n", _ir_decoded_data->hdr_space);
    printf("Bit Mark \t\t: %d\n", _ir_decoded_data->bit_mark);
    printf("One Space \t\t: %d\n", _ir_decoded_data->one_space);
    printf("Zero Space \t\t: %d\n", _ir_decoded_data->zero_space);
    printf("Data Gap \t\t: %d\n", _ir_decoded_data->gap);
    printf("Footer Mark \t\t: %d\n", _ir_decoded_data->ftr_mark);
    printf("Footer Space \t\t: %d\n", _ir_decoded_data->ftr_space);
    printf("Repeat Count \t\t: %d\n", _ir_decoded_data->repeat);

    for(uint8_t i = 0; i < 3; i++)
    {
        printf("Bit Count %d \t\t: %d\n", i, _ir_decoded_data->bits[i]);
    }

    for(uint8_t i = 0; i < 3; i++)
    {
        printf("Hex Value %d first \t: %llX\n", i, _ir_decoded_data->decoded_val[i].first);
        printf("Hex Value %d second \t: %llX\n", i, _ir_decoded_data->decoded_val[i].second);
        printf("Hex Value %d third \t: %llX\n", i, _ir_decoded_data->decoded_val[i].third);
    }

    printf("----------------------------------------------------------------------\n");
}

// set flags for the captured IR Data
void set_flags(ir_decoded_data_t *_ir_decoded_data)
{
    uint8_t _temp_flags = 0;
    bool _temp_compare_1 = false;
    bool _temp_compare_2 = false;

    if(_ir_decoded_data->bits[0] > 0)
    {
        // flag for first packet
        _temp_flags = set_bit(_temp_flags, FIRST_PACKET);
    }
    else
    {
        _temp_flags = clear_bit(_temp_flags, FIRST_PACKET);
    }

    if(_ir_decoded_data->bits[1] > 0)
    {
        // flag for second packet
        _temp_flags = set_bit(_temp_flags, SECOND_PACKET);
    }
    else
    {
        _temp_flags = clear_bit(_temp_flags, SECOND_PACKET);
    }

    if(_ir_decoded_data->bits[2] > 0)
    {
        // flag for third packet
        _temp_flags = set_bit(_temp_flags, THIRD_PACKET);
    }
    else
    {
        _temp_flags = clear_bit(_temp_flags, THIRD_PACKET);
    }

    // flag if there is a footer
    if(_ir_decoded_data->ftr_space > 0)
    {
        // if footer is NEC type footer
        if(_ir_decoded_data->ftr_mark == 0)
        {
            // in NEC type footer, footer mark = header mark
            _temp_flags = set_bit(_temp_flags, NEC_FOOTER);
        }
        else if(_ir_decoded_data->ftr_mark > 0)
        {
            // in unique footer
            _temp_flags = set_bit(_temp_flags, UNIQUE_FOOTER);
        }
    }
    else
    {
        _temp_flags = clear_bit(_temp_flags, NEC_FOOTER);
        _temp_flags = clear_bit(_temp_flags, UNIQUE_FOOTER);
    }

    _temp_compare_1 = compare_hex_value(_ir_decoded_data->decoded_val[0], _ir_decoded_data->decoded_val[1], 
                                        _ir_decoded_data->bits[0], _ir_decoded_data->bits[1]);

    _temp_compare_2 = compare_hex_value(_ir_decoded_data->decoded_val[1], _ir_decoded_data->decoded_val[2], 
                                        _ir_decoded_data->bits[1], _ir_decoded_data->bits[2]);

    if(_ir_decoded_data->bits[0] > 0)
    {
        if(_ir_decoded_data->bits[1] > 0)
        {
            if(_ir_decoded_data->bits[2] > 0)
            {
                if(_temp_compare_1 && _temp_compare_2)
                {
                    ir_val_hex_t _temp_hex_val;
    
                    // all three values are same
                    printf("All three values are same \n");
                    _ir_decoded_data->repeat = REPEAT_TWICE;
                    _ir_decoded_data->bits[1]   =   0;
                    _ir_decoded_data->bits[2]   =   0;

                    // Clear repeat hex values                
                    init_hex_data(&_temp_hex_val);

                    _ir_decoded_data->decoded_val[1] = _temp_hex_val;
                    _ir_decoded_data->decoded_val[2] = _temp_hex_val;
                }
                else
                {
                    // one or two value(s) are different
                    printf("one or two value(s) are different \n");
                    _ir_decoded_data->repeat = NO_REPEAT;
                }
            }
            else
            {
                if(_temp_compare_1)
                {
                    ir_val_hex_t _temp_hex_val;

                    // 0th and 1st values are same
                    printf("0th and 1st values are same \n");
                    _ir_decoded_data->repeat = REPEAT_SINGLE;
                    _ir_decoded_data->bits[1]   =   0;

                    // Clear repeat hex values                
                    init_hex_data(&_temp_hex_val);
                    _ir_decoded_data->decoded_val[1] = _temp_hex_val;
                }
                else
                {
                    // 0th and 1st values are different
                    printf("0th and 1st values are different \n");
                    _ir_decoded_data->repeat = NO_REPEAT;
                }
            }
        }
        else
        {
            // no repeat only one value
            printf("No repeat only one value \n");
            _ir_decoded_data->repeat = NO_REPEAT;
        }
    }

    if(_ir_decoded_data->repeat == REPEAT_SINGLE || _ir_decoded_data->repeat == REPEAT_TWICE)
    {
        _temp_flags = set_bit(_temp_flags, REPEAT);
    }
    else
    {
        _temp_flags = clear_bit(_temp_flags, REPEAT);
    }

    _ir_decoded_data->flags = _temp_flags;
    printf("Flags : 0x%0X\n", _temp_flags);
}

// decode footer
// need to add more validations
void decode_packet(uint16_t pkt_start, uint16_t pkt_end, ir_decoded_data_t *_ir_decoded_data)
{
    uint16_t ftr_space = 0;
    uint16_t _temp_gap = 0;
    uint16_t _temp_ftr_mark = 0;

    // print_decode_data(_ir_decoded_data);

    std::cout << "Packet Start " << pkt_start << " Packet End " << pkt_end << std::endl;
    
    // decode footer gap
    _temp_gap = ir_data[pkt_start];
    
    // If there is no previous gap
    if(_ir_decoded_data->gap > 0)
    {
        // current gap value isn't approximately equal to previous gap
        if(!((_temp_gap > (_ir_decoded_data->gap - ERROR)) && (_temp_gap < (_ir_decoded_data->gap + ERROR))))
        {
            // generate gap value by adding header mark and space
            _ir_decoded_data->gap = _ir_decoded_data->hdr_mark + _ir_decoded_data->hdr_space;
            printf("New Gap generated, %d\n", _ir_decoded_data->gap);
        }
    }
    else
    {
        _ir_decoded_data->gap = _temp_gap;
    }
    
    // decode footer mark
    _temp_ftr_mark = ir_data[pkt_start + 1];
    
    // check if the footer mark stay withing header mark
    if(!((_temp_ftr_mark > (_ir_decoded_data->hdr_mark - ERROR)) && (_temp_ftr_mark < (_ir_decoded_data->hdr_mark + ERROR))))
    {
        _ir_decoded_data->ftr_mark = _temp_ftr_mark;
    }
    else
    {
        // if footer mark is approximately equal to header then no need to save it
        _ir_decoded_data->ftr_mark = 0;
    }

    // decode footer space
    _ir_decoded_data->ftr_space = ir_data[pkt_end];

}

// decode non-footer packets
void decode_packet(uint16_t pkt_start, uint16_t pkt_end, uint16_t pkt_sequence, ir_decoded_data_t *_ir_decoded_data, bool final_pkt)
{
    uint16_t buf_pos = 0;
    uint16_t temp_buf_pos = 0;
    ir_val_hex_t _temp_decoded_hex_value;
    bool init_pck = false;

    uint16_t _temp_zero_space = 0;
    uint16_t _temp_one_space = 0;
    uint16_t _temp_one_space_sum = 0;
    uint8_t temp_count = 0;
    uint16_t _temp_gap = 0;
    
    
    if(final_pkt)
    {
        std::cout << "Packet Type : Final" << std::endl;
        pkt_end ++;     // final bit mark is not able to capture with this interrupt method, so add final bit mark
    }
    else
    {
        std::cout << "Packet Type : Non-Final" << std::endl;
    }

    if(pkt_sequence == 1)
    {
        init_pck = true;
        std::cout << "This is Inital Packet" << std::endl;
    }
    else if(pkt_sequence > 1)
    {
        init_pck = false;
        std::cout << "This is mid/ final Packet" << std::endl;
    }
    
    _temp_decoded_hex_value.first = 0;
    _temp_decoded_hex_value.second = 0;
    _temp_decoded_hex_value.third = 0;
    
    std::cout << "Packet Start " << pkt_start << " Packet End " << pkt_end << std::endl;
    buf_pos = pkt_start;

    

    if(init_pck)
    {

        _ir_decoded_data->hdr_mark = ir_data[++ buf_pos];
        _ir_decoded_data->hdr_space = ir_data[++ buf_pos];
        _ir_decoded_data->bit_mark = ir_data[++ buf_pos];
        _temp_zero_space = ir_data[++ buf_pos];

        for(uint16_t i = buf_pos;  i < pkt_end; i = i + 2)
        {
            if (!(ir_data[i] < _temp_zero_space + ERROR && ir_data[i] > _temp_zero_space - ERROR)) 
            {
                if(ir_data[i] > 0)
                {
                    _temp_one_space_sum += ir_data[i];
                    temp_count ++;
                }
            }
        }
        
        if(_temp_one_space_sum > 0 && temp_count > 0)
        {
            _temp_one_space = _temp_one_space_sum/ temp_count;
            
            if(_temp_one_space > _temp_zero_space)
            {
                _ir_decoded_data->one_space = _temp_one_space;
                _ir_decoded_data->zero_space = _temp_zero_space;
            }
            else
            {
                _ir_decoded_data->one_space = _temp_zero_space;
                _ir_decoded_data->zero_space = _temp_one_space;
            }
        }
        
        temp_count = 0;
        
        // std::cout << "Final Bit : " << ir_data[pkt_end - 1] << std::endl; 
        std::cout << "HDR_MARK : " << _ir_decoded_data->hdr_mark << std::endl;
        std::cout << "HDR_SPACE : " << _ir_decoded_data->hdr_space << std::endl;
        std::cout << "BIT_MARK : " << _ir_decoded_data->bit_mark << std::endl;
        std::cout << "ONE_SPACE : " << _ir_decoded_data->one_space << std::endl;
        std::cout << "ZERO_SPACE : " << _ir_decoded_data->zero_space << std::endl;
    }
    else
    {
        // get the Gap value
        _temp_gap = ir_data[buf_pos];       // buf_start
        printf("Gap : %d\n", _temp_gap);

        if(pkt_sequence == 2)
        {
            // 2nd packet start with the first gap value
            _ir_decoded_data->gap = _temp_gap;
        }
        else if(pkt_sequence > 2)
        {
            // current gap value isn't approximately equal to previous gap
            if(!((_temp_gap > (_ir_decoded_data->gap - ERROR)) && (_temp_gap < (_ir_decoded_data->gap + ERROR))))
            {
                // generate gap value by adding header mark and space
                _ir_decoded_data->gap = _ir_decoded_data->hdr_mark + _ir_decoded_data->hdr_space;
                printf("New Gap generated, %d\n", _ir_decoded_data->gap);
            }
        }


        // need to improve logic, 
        //what happen when the current packet hdr_mark, hdr_space, bit_mark not equal to the previous packet
        temp_buf_pos = buf_pos;
        
        temp_buf_pos ++;
        if((ir_data[temp_buf_pos] > (_ir_decoded_data->hdr_mark - ERROR)) && (ir_data[temp_buf_pos] < (_ir_decoded_data->hdr_mark + ERROR)))
        {
            std::cout << "Header Mark withing Range" << std::endl;

            temp_buf_pos ++;
            if((ir_data[temp_buf_pos] > (_ir_decoded_data->hdr_space - ERROR)) && (ir_data[temp_buf_pos] < (_ir_decoded_data->hdr_space + ERROR)))
            {
                std::cout << "Header Space withing Range" << std::endl;

                temp_buf_pos ++;
                if((ir_data[temp_buf_pos] > (_ir_decoded_data->bit_mark - ERROR)) && (ir_data[temp_buf_pos] < (_ir_decoded_data->bit_mark + ERROR)))
                {
                    std::cout << "Bit Mark withing Range" << std::endl;
                    temp_buf_pos ++;

                    buf_pos = temp_buf_pos;
                }
                else
                {
                    std::cout << "Bit Mark outof Range" << std::endl;

                }
            }
            else
            {
                std::cout << "Header Space Outof Range" << std::endl;
            }
        }
        else
        {
            std::cout << "Header Mark Outof Range" << std::endl;
        }
    }
    
    if((_ir_decoded_data->hdr_mark > 0) && (_ir_decoded_data->hdr_space > 0) && (_ir_decoded_data->bit_mark > 0)
        && (_ir_decoded_data->one_space > 0) && (_ir_decoded_data->zero_space > 0))
    {
        std::cout << "Complete IR Packet Received" << std::endl;
        
        std::cout << "Buf pos : " << buf_pos << " Pkt End : " << pkt_end << std::endl;
        
        for(uint16_t i = buf_pos;  i < pkt_end; i = i + 2)
        {
            if((ir_data[i] > (_ir_decoded_data->zero_space - ERROR)) && (ir_data[i] < (_ir_decoded_data->zero_space + ERROR)))
            {    
            }
            
            else if((ir_data[i] > (_ir_decoded_data->one_space - ERROR)) && (ir_data[i] < (_ir_decoded_data->one_space + ERROR)))
            {
                std::cout << "1 - " << temp_count << std::endl;
                
                if(temp_count < 64)
                {
                    _temp_decoded_hex_value.first = (1ull << temp_count) | _temp_decoded_hex_value.first;
                }
                else if(temp_count < 128)
                {
                    _temp_decoded_hex_value.second = (1ull << (temp_count - 64)) | _temp_decoded_hex_value.second;
                }
                else
                {
                    _temp_decoded_hex_value.third = (1ull << (temp_count - 128)) | _temp_decoded_hex_value.third;
                }
            }
            
            temp_count ++;
        }
        
        // set decoded hex values and bit count to the struct
        printf("Packet Sequence : %d\n", pkt_sequence);
        if(pkt_sequence > 0 && pkt_sequence <= 3)
        {
            _ir_decoded_data->decoded_val[pkt_sequence - 1] = _temp_decoded_hex_value;
            _ir_decoded_data->bits[pkt_sequence - 1] = temp_count;
        }

        std::cout << "Bit Count : " << temp_count << std::endl; 
        std::cout << "First Hex Value : " << std::hex<< _temp_decoded_hex_value.first << std::endl;
        std::cout << "Second Hex Value : " << std::hex << _temp_decoded_hex_value.second << std::endl;
        std::cout << "Third Hex Value : " << std::hex << _temp_decoded_hex_value.third << std::endl;
        std::cout << std::dec << std::endl;
    }
    else
    {
        std::cout << "Receive fail" << std::endl;
    }
}

// receive IR packet
void receive_ir_packet(uint32_t remote_id, uint8_t cmd, uint8_t communication_id)
{
    ir_decoded_data_t ir_decoded_data;
    uint16_t offset_start = 0;
    uint16_t pkt_end = 0;
    uint16_t pkt_seq_count = 0;
    
    int size_buf = sizeof(ir_data)/sizeof(uint16_t);
    std::cout << "Size: "<< size_buf << std::endl;
    
    if(size_buf > MIN_PACKET_SIZE)
    {
        uint16_t temp_max = 0;

        offset_start = 0;
        init_decode_data(&ir_decoded_data);

        while(pkt_end < (size_buf - 1))
        {
            
            if((size_buf - offset_start) > (MIN_DATA_BITS * 2))
            {
                uint16_t temp_hdr_mark = ir_data[offset_start + 1];
                uint16_t temp_hdr_space = ir_data[offset_start + 2];
                std::cout << std::endl;
                std::cout << "Temp HDR_MARK : " << temp_hdr_mark << " Temp HDR_SPACE : " << temp_hdr_space << std::endl;
                
                if(temp_hdr_mark > temp_hdr_space)
                {
                    temp_max = temp_hdr_mark;
                }
                else
                {
                    temp_max = temp_hdr_space;
                }
                
                std::cout << "Max Value : " << temp_max << std::endl;
                // offset_start = offset_start + 3;
                
                for(int i = offset_start + 3; i < size_buf; i++)
                {
                    if(ir_data[i] > temp_max)
                    {
                        pkt_end = i;
                        pkt_seq_count ++;
                        std::cout << "Current Packet " << pkt_seq_count << " end at " << pkt_end << " another packet available"<< std::endl;
                        decode_packet(offset_start, pkt_end, pkt_seq_count, &ir_decoded_data, false);
                        break;
                    }
                    else
                    {
                        pkt_end = i;
                        if(pkt_end == size_buf - 1)
                        {
                            pkt_seq_count++;
                            std::cout << "Packet " << pkt_seq_count << " End at " << pkt_end << " this is final packet" << std::endl;
                            decode_packet(offset_start, pkt_end, pkt_seq_count, &ir_decoded_data, true);
                        }
                    }
                }
                
                offset_start = pkt_end;
            }
            else
            {
                std::cout << "Footer available at " << offset_start << std::endl;  
                // packet end = buffer Size - 1;
                decode_packet(offset_start, (size_buf - 1), &ir_decoded_data);
                break;
            }
        }

        print_decode_data(&ir_decoded_data);
        set_flags(&ir_decoded_data);
        print_decode_data(&ir_decoded_data);
        
        send_ir_can_message(ir_decoded_data, &remote_id, &cmd, &communication_id);
    }
    else
    {
        std::cout << "Invalid Data Packet Length - " << size_buf << std::endl;
    }
}

// function to generate CAN messages
void send_ir_can_message(ir_decoded_data_t _ir_decode_data, uint32_t *remote_id, uint8_t *cmd, uint8_t *communication_id)
{
    unsigned char can_message[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int _temp_packet_count = 0;

    _temp_packet_count = bit_get(_ir_decode_data.flags, FIRST_PACKET)
                            + bit_get(_ir_decode_data.flags, SECOND_PACKET)
                            + bit_get(_ir_decode_data.flags, THIRD_PACKET);
    
    printf("Packet Count %d\n", _temp_packet_count);

    if(_temp_packet_count > 0)
    {
        uint8_t seq_no = 0;
        
        
        // generate 1st static CAN Message 
        seq_no ++;
        can_message[0] = seq_no;
        can_message[1] = *communication_id;
        can_message[2] = (*remote_id >>  0) & 0xFF;
        can_message[3] = (*remote_id >>  8) & 0xFF;
        can_message[4] = (*remote_id >> 16) & 0xFF;
        can_message[5] = *cmd;
        can_message[6] = (_ir_decode_data.hdr_mark >> 0) & 0xFF;;
        can_message[7] = (_ir_decode_data.hdr_mark >> 8) & 0xFF;;
        
        printf("Message Sequence : %d | %x %x %x %x %x %x %x %x\n", 
                    seq_no, can_message[0], can_message[1], can_message[2], can_message[3],
                    can_message[4], can_message[5], can_message[6], can_message[7]);
                    
        
        // generate 2nd static CAN Message
        seq_no ++;
        can_message[0] = seq_no;
        can_message[1] = *communication_id;
        can_message[2] = (_ir_decode_data.hdr_space >> 0) & 0xFF;
        can_message[3] = (_ir_decode_data.hdr_space >> 8) & 0xFF;
        can_message[4] = (_ir_decode_data.bit_mark >> 0) & 0xFF;
        can_message[5] = (_ir_decode_data.bit_mark >> 8) & 0xFF;
        can_message[6] = (_ir_decode_data.zero_space >> 0) & 0xFF;
        can_message[7] = (_ir_decode_data.zero_space >> 8) & 0xFF;
        
        printf("Message Sequence : %d | %x %x %x %x %x %x %x %x\n", 
                    seq_no, can_message[0], can_message[1], can_message[2], can_message[3],
                    can_message[4], can_message[5], can_message[6], can_message[7]);
        
        
        // generate 3rd static CAN Message
        seq_no ++;
        can_message[0] = seq_no;
        can_message[1] = *communication_id;
        can_message[2] = (_ir_decode_data.one_space >> 0) & 0xFF;
        can_message[3] = (_ir_decode_data.one_space >> 8) & 0xFF;
        can_message[4] = _ir_decode_data.flags;
        
        if(_temp_packet_count == 1)
        {
            can_message[5] = _ir_decode_data.bits[0];
            can_message[6] = 0;
            can_message[7] = 0;
        }
        else if(_temp_packet_count == 2)
        {
            can_message[5] = _ir_decode_data.bits[0];
            can_message[6] = _ir_decode_data.bits[1];
            can_message[7] = 0;
        }
        else if(_temp_packet_count == 3)
        {
            can_message[5] = _ir_decode_data.bits[0];
            can_message[6] = _ir_decode_data.bits[1];
            can_message[7] = _ir_decode_data.bits[2];
        }
        
        printf("Message Sequence : %d | %x %x %x %x %x %x %x %x\n", 
                    seq_no, can_message[0], can_message[1], can_message[2], can_message[3],
                    can_message[4], can_message[5], can_message[6], can_message[7]);
        
        
        if(bit_get(_ir_decode_data.flags, NEC_FOOTER) == 1)
        {
            printf("NEC Footer available\n");
            // generate 4th static CAN Message
            seq_no ++;
            can_message[0] = seq_no;
            can_message[1] = *communication_id;
            can_message[2] = (_ir_decode_data.gap >> 0) & 0xFF;
            can_message[3] = (_ir_decode_data.gap >> 8) & 0xFF;
            can_message[4] = (_ir_decode_data.ftr_space >> 0) & 0xFF;
            can_message[5] = (_ir_decode_data.ftr_space >> 8) & 0xFF;
            can_message[6] = 0;
            can_message[7] = 0;
            
            printf("Message Sequence : %d | %x %x %x %x %x %x %x %x\n", 
                    seq_no, can_message[0], can_message[1], can_message[2], can_message[3],
                    can_message[4], can_message[5], can_message[6], can_message[7]);
            
        }
        else if(bit_get(_ir_decode_data.flags, UNIQUE_FOOTER) == 1)
        {
            printf("Unique Footer available\n");
            // generate 4th static CAN Message
            seq_no ++;
            can_message[0] = seq_no;
            can_message[1] = *communication_id;
            can_message[2] = (_ir_decode_data.gap >> 0) & 0xFF;
            can_message[3] = (_ir_decode_data.gap >> 8) & 0xFF;
            can_message[4] = (_ir_decode_data.ftr_space >> 0) & 0xFF;
            can_message[5] = (_ir_decode_data.ftr_space >> 8) & 0xFF;
            can_message[6] = (_ir_decode_data.ftr_mark >> 0) & 0xFF;
            can_message[7] = (_ir_decode_data.ftr_mark >> 8) & 0xFF;
            
            printf("Message Sequence : %d | %x %x %x %x %x %x %x %x\n", 
                    seq_no, can_message[0], can_message[1], can_message[2], can_message[3],
                    can_message[4], can_message[5], can_message[6], can_message[7]);
            
            
            
        }else if((bit_get(_ir_decode_data.flags, NEC_FOOTER) == 0) && 
                (bit_get(_ir_decode_data.flags, UNIQUE_FOOTER) == 0)) 
        {
            // check this part
            printf("No Footer available\n");
            // generate 4th static CAN Message
            seq_no ++;
            can_message[0] = seq_no;
            can_message[1] = *communication_id;
            can_message[2] = (_ir_decode_data.gap >> 0) & 0xFF;
            can_message[3] = (_ir_decode_data.gap >> 8) & 0xFF;
            can_message[4] = 0;
            can_message[5] = 0;
            can_message[6] = 0;
            can_message[7] = 0;
            
            printf("Message Sequence : %d | %x %x %x %x %x %x %x %x\n", 
                    seq_no, can_message[0], can_message[1], can_message[2], can_message[3],
                    can_message[4], can_message[5], can_message[6], can_message[7]);
        }
        
        can_send_hex_value(_ir_decode_data, &seq_no, *communication_id, 0);
        
        if(_temp_packet_count == 2)
        {
            if(bit_get(_ir_decode_data.flags, REPEAT) == 0)
            {
                can_send_hex_value(_ir_decode_data, &seq_no, *communication_id, 1);    
            }
        }
        
        else if(_temp_packet_count == 3)
        {
            if(bit_get(_ir_decode_data.flags, REPEAT) == 0)
            {
                can_send_hex_value(_ir_decode_data, &seq_no, *communication_id, 1);
                can_send_hex_value(_ir_decode_data, &seq_no, *communication_id, 2);
            }
        }
    }
    else
    {
        printf("no packet available\n");
    }
}

// function to generate CAN messages for the hex value 
void can_send_hex_value(ir_decoded_data_t _ir_decode_data, uint8_t *seq_no, uint8_t communication_id, uint8_t pkt_num)
{
    unsigned char can_message[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t _temp_seq_no = 0;
    
    _temp_seq_no = *seq_no;
    _temp_seq_no ++;
    can_message[0] = _temp_seq_no;
    can_message[1] = communication_id;
    can_message[2] = (_ir_decode_data.decoded_val[pkt_num].first >>  0) & 0xFF;
    can_message[3] = (_ir_decode_data.decoded_val[pkt_num].first >>  8) & 0xFF;
    can_message[4] = (_ir_decode_data.decoded_val[pkt_num].first >> 16) & 0xFF;
    can_message[5] = (_ir_decode_data.decoded_val[pkt_num].first >> 24) & 0xFF;
    can_message[6] = (_ir_decode_data.decoded_val[pkt_num].first >> 32) & 0xFF;
    can_message[7] = (_ir_decode_data.decoded_val[pkt_num].first >> 40) & 0xFF;
    
    printf("Message Sequence : %d | %x %x %x %x %x %x %x %x\n", 
            _temp_seq_no, can_message[0], can_message[1], can_message[2], can_message[3],
            can_message[4], can_message[5], can_message[6], can_message[7]);
     
    _temp_seq_no ++;
    can_message[0] = _temp_seq_no;
    can_message[1] = communication_id;
    can_message[2] = (_ir_decode_data.decoded_val[pkt_num].first >> 48) & 0xFF;
    can_message[3] = (_ir_decode_data.decoded_val[pkt_num].first >> 56) & 0xFF;
    can_message[4] = (_ir_decode_data.decoded_val[pkt_num].second >>  0) & 0xFF;
    can_message[5] = (_ir_decode_data.decoded_val[pkt_num].second >>  8) & 0xFF;
    can_message[6] = (_ir_decode_data.decoded_val[pkt_num].second >> 16) & 0xFF;
    can_message[7] = (_ir_decode_data.decoded_val[pkt_num].second >> 24) & 0xFF;
    
    printf("Message Sequence : %d | %x %x %x %x %x %x %x %x\n", 
            _temp_seq_no, can_message[0], can_message[1], can_message[2], can_message[3],
            can_message[4], can_message[5], can_message[6], can_message[7]);
    
    _temp_seq_no ++;
    can_message[0] = _temp_seq_no;
    can_message[1] = communication_id;
    can_message[2] = (_ir_decode_data.decoded_val[pkt_num].second >> 32) & 0xFF;
    can_message[3] = (_ir_decode_data.decoded_val[pkt_num].second >> 40) & 0xFF;
    can_message[4] = (_ir_decode_data.decoded_val[pkt_num].second >> 48) & 0xFF;
    can_message[5] = (_ir_decode_data.decoded_val[pkt_num].second >> 56) & 0xFF;
    can_message[6] = (_ir_decode_data.decoded_val[pkt_num].third >>  0) & 0xFF;
    can_message[7] = (_ir_decode_data.decoded_val[pkt_num].third >>  8) & 0xFF;
    
    printf("Message Sequence : %d | %x %x %x %x %x %x %x %x\n", 
            _temp_seq_no, can_message[0], can_message[1], can_message[2], can_message[3],
            can_message[4], can_message[5], can_message[6], can_message[7]);
            
    _temp_seq_no ++;
    can_message[0] = _temp_seq_no;
    can_message[1] = communication_id;
    can_message[2] = (_ir_decode_data.decoded_val[pkt_num].third >> 16) & 0xFF;
    can_message[3] = (_ir_decode_data.decoded_val[pkt_num].third >> 24) & 0xFF;
    can_message[4] = (_ir_decode_data.decoded_val[pkt_num].third >> 32) & 0xFF;
    can_message[5] = (_ir_decode_data.decoded_val[pkt_num].third >> 40) & 0xFF;
    can_message[6] = (_ir_decode_data.decoded_val[pkt_num].third >> 48) & 0xFF;
    can_message[7] = (_ir_decode_data.decoded_val[pkt_num].third >> 56) & 0xFF;
    
    printf("Message Sequence : %d | %x %x %x %x %x %x %x %x\n", 
            _temp_seq_no, can_message[0], can_message[1], can_message[2], can_message[3],
            can_message[4], can_message[5], can_message[6], can_message[7]);
    
    *seq_no = _temp_seq_no;
}