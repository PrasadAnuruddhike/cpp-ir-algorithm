#include <iostream>


// Packet without footer, HDR_MARK < HDR_SPACE
// uint16_t ir_data[] = {
//                         31074, 
//                         4567, 9345, 
//                         572, 1691, 576, 1691, 570, 1691, 573, 560, 573, 560, 569, 560, 572, 559, 574, 1691,
//                         568, 1697, 572, 559, 570, 558, 573, 1694, 573, 1689, 569, 1687, 572, 559, 574, 558
//                     };

// Packet with footer, HDR_MARK > HDR_SPACE
// bits, HDR_MARK, HDR_SPACE, BIT_MARK, ONE_SPACE, ZERO_SPACE, GAP, FTR_SPACE, hex_value
// uint16_t ir_data[] = {
//                         31074, 
//                         9345, 4567, 
//                         572, 1691, 576, 1691, 570, 1691, 573, 560, 573, 560, 569, 560, 572, 559, 574, 558, 
//                         568, 1697, 572, 559, 570, 558, 573, 1694, 573, 1689, 569, 1687, 572, 559, 574, 558,
//                         574, 
//                         10967, 
//                         9345, 2365
//                     };

// Packet with footer, HDR_MARK < HDR_SPACE
// uint16_t ir_data[] = {
//                         31074, 
//                         4567, 9347, 
//                         572, 1691, 576, 1691, 570, 1691, 573, 560, 573, 560, 569, 560, 572, 559, 574, 558,  // 18
//                         568, 1697, 572, 559, 570, 558, 573, 1694, 573, 1689, 569, 1687, 572, 559, 574, 558,
//                         574,                                                                
//                         10967,                                                                              // 20
//                         4578, 2365                                                                          // 22
//                     };

// // Same Packet Repeat, HDR_MARK > HDR_SPACE 
// bits, HDR_MARK, HDR_SPACE, BIT_MARK, ONE_SPACE, ZERO_SPACE, GAP, hex_value, RPT_COUNT
// uint16_t ir_data[] = {
//                         31074, 
//                         9345, 4567, 
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,  
//                         568, 1690, 572, 559, 570, 558, 573, 1694, 573, 1689, 569, 1687, 572, 559, 574, 558,
//                         574,                                                                                
//                         12031,                                                                              
//                         9341, 4562,                                                                         
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,  
//                         568, 1697, 572, 559, 570, 558, 573, 1694, 573, 1689, 569, 1687, 572, 559, 574, 558
//                     };

// uint16_t ir_data[] = {
//                         31074, 
//                         9345, 4567, 
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,  
//                         568, 1690, 572, 559, 570, 558, 573, 1694, 573, 1689, 569, 1687, 572, 559, 574, 558,
//                         574,                                                                                
//                         12031,                                                                              
//                         9341, 4562,                                                                         
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,  
//                         568, 1697, 572, 559, 570, 558, 573, 1694, 573, 1689, 569, 1687, 572, 559, 574, 558,
//                         574,                                                                                
//                         12031,                                                                              
//                         9341, 4562,                                                                         
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,  
//                         568, 1697, 572, 559, 570, 558, 573, 1694, 573, 1689, 569, 1687, 572, 559, 574, 558,
//                         574, 
//                         12031,                                                                              
//                         9341, 2365
//                     };

// Same Packet Repeat, HDR_MARK < HDR_SPACE
// uint16_t ir_data[] = {
//                         31074, 
//                         4567, 9345,
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,  
//                         568, 1697, 572, 559, 570, 558, 573, 1694, 573, 1689, 569, 1687, 572, 559, 574, 558,
//                         574,
//                         12031,
//                         4567, 9345,
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,  
//                         568, 1697, 572, 559, 570, 558, 573, 1694, 573, 1689, 569, 1687, 572, 559, 574, 558,
//                     };

// Different Packets, HDR_MARK < HDR_SPACE
// bits1, bits2, HDR_MARK, HDR_SPACE, BIT_MARK, ONE_SPACE, ZERO_SPACE, GAP, hex_value1, hex_value2
// uint16_t ir_data[] = {
//                         31074, 
//                         9345, 4567,
//                         572, 1691, 576, 1691, 570, 1691, 573, 560, 573, 560, 569, 560, 572, 559, 574, 558, 
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691, 
//                         574,
//                         12031,
//                         9345, 4567,
//                         575, 562, 573, 565, 568, 564, 573, 1698, 573, 562, 575, 562, 571, 562, 576, 558, 
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691, 					
//                         574, 1700, 573, 1698, 573, 1700, 572, 561, 575, 1696, 575, 1696, 577, 1698, 573, 1700
//                     };

// // Different Packets, HDR_MARK > HDR_SPACE
// uint16_t ir_data[] = {
//                         31074, 
//                         4567, 9345,
//                         572, 1691, 576, 1691, 570, 1691, 573, 560, 573, 560, 569, 560, 572, 559, 574, 558, 
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691, 
//                         574,
//                         12031,
//                         4561, 9342,
//                         575, 562, 573, 565, 568, 564, 573, 1698, 573, 562, 575, 562, 571, 562, 576, 558, 
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691, 					
//                         574, 1700, 573, 1698, 573, 1700, 572, 561, 575, 1696, 575, 1696, 577, 1698, 573, 1700
//                     };


// Different Packets with invalid 2nd packet, HDR_MARK > HDR_SPACE
// uint16_t ir_data[] = {
//                         31074, 
//                         4567, 9345,
//                         572, 1691, 576, 1691, 570, 1691, 573, 560, 573, 560, 569, 560, 572, 559, 574, 558, 
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691, 
//                         574,
//                         12031,
//                         4561, 456,
//                         575, 562, 573, 565, 568, 564, 573, 1698, 573, 562, 575, 562, 571, 562, 576, 558, 
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691, 					
//                         574, 1700, 573, 1698, 573, 1700, 572, 561, 575, 1696, 575, 1696, 577, 1698, 573, 1700
//                     };
          
// Different Packets with footer, HDR_MARK > HDR_SPACE          
// bits1, bits2, HDR_MARK, HDR_SPACE, BIT_MARK, ONE_SPACE, ZERO_SPACE, GAP, FTR_SPACE, hex_value1, hex_value2
uint16_t ir_data[] = {
                        31074, 
                        4567, 9345,
                        572, 1691, 576, 1691, 570, 1691, 573, 560, 573, 560, 569, 560, 572, 559, 574, 558, 
                        571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,  
                        574,
                        12031,
                        4560, 9345,
                        575, 562, 573, 565, 568, 564, 573, 1698, 573, 562, 575, 562, 571, 562, 576, 558, 
                        571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691, 					
                        574, 1700, 573, 1698, 573, 1700, 572, 561, 575, 1696, 575, 1696, 577, 1698, 573, 1700,
                        574, 
                        12967, 
                        4567, 2365
                    };

// Three Different packets
// bits1, bits2, bits3, HDR_MARK, HDR_SPACE, BIT_MARK, ONE_SPACE, ZERO_SPACE, GAP, FTR_SPACE, hex_value1, hex_value2, hex_value3
// uint16_t ir_data[] = {
//                         31074, 
//                         4567, 9345,                                                                             // 2
//                         572, 1691, 576, 1691, 570, 1691, 573, 560, 573, 560, 569, 560, 572, 559, 574, 558,      // 18
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,     // 34
//                         574,                                                                                    // 35
//                         12931,                                                                                  // 36
//                         4560, 9345,                                                                             // 38
//                         575, 562, 573, 565, 568, 564, 573, 1698, 573, 562, 575, 562, 571, 562, 576, 558,        // 54
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,     // 70		
//                         574, 1700, 573, 1698, 573, 1700, 572, 561, 575, 1696, 575, 1696, 577, 1698, 573, 1700,  // 86
//                         574, 
//                         12967, 
//                         4560, 9345,                                                                             // 90
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,     // 106
//                         574, 1700, 573, 1698, 573, 1700, 572, 561, 575, 1696, 575, 1696, 577, 1698, 573, 1700,
//                         572, 1691, 576, 1691, 570, 1691, 573, 560, 573, 560, 569, 560, 572, 559, 574, 558, 
//                         575, 562, 573, 565, 568, 564, 573, 1698, 573, 562, 575, 562, 571, 562, 576, 558         // 154
//                     };

// Three Different packets with footer
// uint16_t ir_data[] = {
//                         31074, 
//                         4567, 9345,                                                                             // 2
//                         572, 1691, 576, 1691, 570, 1691, 573, 560, 573, 560, 569, 560, 572, 559, 574, 558,      // 18
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,     // 34
//                         574,                                                                                    // 35
//                         12931,                                                                                  // 36
//                         4560, 9345,                                                                             // 38
//                         575, 562, 573, 565, 568, 564, 573, 1698, 573, 562, 575, 562, 571, 562, 576, 558,        // 54
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,     // 70		
//                         574, 1700, 573, 1698, 573, 1700, 572, 561, 575, 1696, 575, 1696, 577, 1698, 573, 1700,  // 86
//                         574, 
//                         12967, 
//                         4560, 9345,                                                                             // 90
//                         571, 1680, 578, 1695, 561, 566, 570, 560, 563, 552, 559, 1689, 569, 551, 568, 1691,     // 106
//                         574, 1700, 573, 1698, 573, 1700, 572, 561, 575, 1696, 575, 1696, 577, 1698, 573, 1700,
//                         572, 1691, 576, 1691, 570, 1691, 573, 560, 573, 560, 569, 560, 572, 559, 574, 558, 
//                         575, 562, 573, 565, 568, 564, 573, 1698, 573, 562, 575, 562, 571, 562, 576, 558,        // 154
//                         574, 
//                         12750, 
//                         4567, 2365
//                     };

// uint16_t ir_data[] = {
//                         60196, 
//                         3485, 1755,  
//                         393, 495, 398, 1283, 397, 496, 396, 496, 396, 497, 396, 505, 398, 495, 397, 495, 						// 0000 0010
//                         398, 494, 398, 493, 399, 497, 396, 496, 392, 497, 397, 1287, 393, 499, 394, 496, 						// 0010 0000
//                         396, 496, 396, 496, 396, 497, 394, 498, 398, 494, 399, 1280, 400, 1284, 394, 1287, 						// 1110 0000
//                         393, 499, 395, 495, 396, 1284, 398, 495, 398, 494, 398, 494, 398, 495, 398, 496, 						// 0000 0100
//                         392, 500, 397, 496, 394, 498, 394, 495, 397, 495, 397, 499, 394, 496, 396, 496, 						// 0000 0000
//                         396, 1285, 398, 494, 395, 497, 394, 499, 398, 1281, 399, 1281, 397, 495, 398, 498, 						// 0011 0001
//                         394, 496, 396, 497, 395, 497, 394, 498, 394, 498, 399, 1280, 400, 496, 393, 499, 						// 0010 0000
//                         392, 497, 397, 494, 399, 498, 394, 495, 397, 494, 399, 496, 396, 496, 396, 1284, 						// 1000 0000
//                         394, 1286, 399, 492, 400, 496, 392, 500, 396, 493, 397, 1283, 398, 498, 394, 1284,						// 1010 0001 
//                         397, 496, 398, 494, 395, 498, 393, 499, 398, 496, 393, 496, 395, 497, 400, 496, 						// 0000 0000
//                         394, 499, 393, 495, 397, 495, 398, 495, 397, 497, 395, 497, 396, 496, 394, 498, 						// 0000 0000
//                         394, 499, 394, 1284, 396, 1289, 393, 495, 398, 494, 398, 499, 393, 495, 398, 496,						// 0000 0110
//                         396, 496, 396, 496, 396, 497, 393, 499, 394, 498, 394, 1285, 395, 1285, 398, 494, 						// 0110 0000
//                         398, 494, 398, 495, 398, 493, 399, 493, 399, 497, 396, 496, 394, 495, 397, 494, 						// 0000 0000
//                         398, 499, 394, 495, 397, 496, 396, 497, 396, 496, 393, 499, 395, 497, 394, 499, 						// 0000 0000
//                         393, 499, 394, 496, 396, 497, 395, 497, 395, 497, 398, 494, 398, 495, 398, 1284, 						// 1000 0000
//                         396, 496, 396, 496, 394, 499, 393, 499, 394, 495, 397, 499, 394, 496, 396, 496,						 	// 0000 0000
//                         396, 497, 395, 1285, 394, 1288, 393, 500, 396, 496, 396, 496, 394, 495, 397, 495, 						// 0000 0110
//                         398, 498, 394, 497, 395, 1285, 396, 496, 398, 494, 395, 1286, 394, 1288, 393, 500,						// 0110 0100
//                         392, 
//                         10152, 
//                         3544, 1746,
//                         393, 495, 398, 1283, 397, 496, 396, 496, 396, 497, 396, 505, 398, 495, 397, 495, 						
//                         398, 494, 398, 493, 399, 497, 396, 496, 392, 497, 397, 1287, 393, 499, 394, 496, 						
//                         396, 496, 396, 496, 396, 497, 394, 498, 398, 494, 399, 1280, 400, 1284, 394, 1287, 						
//                         393, 499, 395, 495, 396, 1284, 398, 495, 398, 494, 398, 494, 398, 495, 398, 496, 						
//                         392, 500, 397, 496, 394, 498, 394, 495, 397, 495, 397, 499, 394, 496, 396, 496, 						
//                         396, 1285, 398, 494, 395, 497, 394, 499, 398, 1281, 399, 1281, 397, 495, 398, 498, 						
//                         394, 496, 396, 497, 395, 497, 394, 498, 394, 498, 399, 1280, 400, 496, 393, 499, 						
//                         392, 497, 397, 494, 399, 498, 394, 495, 397, 494, 399, 496, 396, 496, 396, 1284, 						
//                         394, 1286, 399, 492, 400, 496, 392, 500, 396, 493, 397, 1283, 398, 498, 394, 1284,						 
//                         397, 496, 398, 494, 395, 498, 393, 499, 398, 496, 393, 496, 395, 497, 400, 496, 						
//                         394, 499, 393, 495, 397, 495, 398, 495, 397, 497, 395, 497, 396, 496, 394, 498, 						
//                         394, 499, 394, 1284, 396, 1289, 393, 495, 398, 494, 398, 499, 393, 495, 398, 496,						
//                         396, 496, 396, 496, 396, 497, 393, 499, 394, 498, 394, 1285, 395, 1285, 398, 494, 						
//                         398, 494, 398, 495, 398, 493, 399, 493, 399, 497, 396, 496, 394, 495, 397, 494, 						
//                         398, 499, 394, 495, 397, 496, 396, 497, 396, 496, 393, 499, 395, 497, 394, 499, 						
//                         393, 499, 394, 496, 396, 497, 395, 497, 395, 497, 398, 494, 398, 495, 398, 1284, 						
//                         396, 496, 396, 496, 394, 499, 393, 499, 394, 495, 397, 499, 394, 496, 396, 496,						 	
//                         396, 497, 395, 1285, 394, 1288, 393, 500, 396, 496, 396, 496, 394, 495, 397, 495, 						
//                         398, 498, 394, 497, 395, 1275, 396, 496, 398, 494, 395, 1286, 394, 1288, 393, 500,
//                         392, 
//                         10159, 
//                         3544, 1746,
//                         393, 495, 398, 1283, 397, 496, 396, 496, 396, 497, 396, 505, 398, 495, 397, 495, 						
//                         398, 494, 398, 493, 399, 497, 396, 496, 392, 497, 397, 1287, 393, 499, 394, 496, 						
//                         396, 496, 396, 496, 396, 497, 394, 498, 398, 494, 399, 1280, 400, 1284, 394, 1287, 						
//                         393, 499, 395, 495, 396, 1284, 398, 495, 398, 494, 398, 494, 398, 495, 398, 496, 						
//                         392, 500, 397, 496, 394, 498, 394, 495, 397, 495, 397, 499, 394, 496, 396, 496, 						
//                         396, 1285, 398, 494, 395, 497, 394, 499, 398, 1281, 399, 1281, 397, 495, 398, 498, 						
//                         394, 496, 396, 497, 395, 497, 394, 498, 394, 498, 399, 1280, 400, 496, 393, 499, 						
//                         392, 497, 397, 494, 399, 498, 394, 495, 397, 494, 399, 496, 396, 496, 396, 1284, 						
//                         394, 1286, 399, 492, 400, 496, 392, 500, 396, 493, 397, 1283, 398, 498, 394, 1284,						 
//                         397, 496, 398, 494, 395, 498, 393, 499, 398, 496, 393, 496, 395, 497, 400, 496, 						
//                         394, 499, 393, 495, 397, 495, 398, 495, 397, 497, 395, 497, 396, 496, 394, 498, 						
//                         394, 499, 394, 1284, 396, 1289, 393, 495, 398, 494, 398, 499, 393, 495, 398, 496,						
//                         396, 496, 396, 496, 396, 497, 393, 499, 394, 498, 394, 1285, 395, 1285, 398, 494, 						
//                         398, 494, 398, 495, 398, 493, 399, 493, 399, 497, 396, 496, 394, 495, 397, 494, 						
//                         398, 499, 394, 495, 397, 496, 396, 497, 396, 496, 393, 499, 395, 497, 394, 499, 						
//                         393, 499, 394, 496, 396, 497, 395, 497, 395, 497, 398, 494, 398, 495, 398, 1284, 						
//                         396, 496, 396, 496, 394, 499, 393, 499, 394, 495, 397, 499, 394, 496, 396, 496,						 	
//                         396, 497, 395, 1285, 394, 1288, 393, 500, 396, 496, 396, 496, 394, 495, 397, 495, 						
//                         398, 498, 394, 490, 395, 1265, 396, 496, 398, 494, 395, 1286, 394, 1288, 393, 500,						
//                         // 389, 
//                         // 10150, 
//                         // 3544, 2365
//                     };

#define MIN_DATA_BITS       8
#define MIN_PACKET_SIZE     34          // Junk + HDR_MARK + HDR_SPACE + (DATA_BITS x 2) --> DATA_BITS = 16
#define IR_HEADER_LENGTH    2           // HDR_MARK + HDR_SPACE
#define IR_GAP_LENGTH       4           // (n-1)END_BIT + GAP + HDR_MARK + HDR_SPACE
#define IR_FOOTER_LENGTH    4           // (n-1)END_BIT + GAP + HDR_MARK + HDR_SPACE
#define IR_END_LENGTH       2           // END_BIT + END_SPACE
#define IR_END_SPACE        5000

uint16_t ERROR = 80;

// uint16_t *generated_ir_data;

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

void print_can_message(unsigned char *_can_message);
void print_ir_buffer(uint16_t *_buf, int16_t size_buf);

int set_bit(int n, int k);
int clear_bit(int n, int k);
int toggle_bit(int n, int k);
int get_bit(int n, int k);



void generate_rcv_can_message();
void prepare_data_array(uint8_t *_data, unsigned char *_can_message);

void ir_rd_packet_handler(unsigned char *_can_message);
void ir_rd_data_packet(uint8_t *_seq_no, uint8_t *_data, uint8_t *communication_id);

void generate_ir_signal();
int16_t calc_bit_count();
int section_count();

void gen_ir_pattern_single_section(uint8_t _bits, ir_val_hex_t _decoded_val, int *_buf_counter, uint16_t *_ir_buf);
void gen_ir_gap(int *_buf_counter, uint16_t *_ir_buf);
void gen_ir_end(int *_buf_counter, uint16_t *_ir_buf);
void gen_ir_footer(int *_buf_counter, uint16_t *_ir_buf, bool is_nec);

ir_decoded_data_t received_ir_decoded_data;

int main()
{
    uint32_t remote_id;
    uint8_t cmd;
    uint8_t communication_id;



    remote_id = 0x23AC09;
    cmd = 0x17;
    communication_id = 0x7A;

    int size_buf = sizeof(ir_data)/sizeof(uint16_t);

    // print_ir_buffer(ir_data, size_buf);
    // receive_ir_packet(remote_id, cmd, communication_id);
    generate_rcv_can_message();
    

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
int get_bit(int n, int k)
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

    _temp_packet_count = get_bit(_ir_decode_data.flags, FIRST_PACKET)
                            + get_bit(_ir_decode_data.flags, SECOND_PACKET)
                            + get_bit(_ir_decode_data.flags, THIRD_PACKET);
    
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
        
        
        if(get_bit(_ir_decode_data.flags, NEC_FOOTER) == 1)
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
        else if(get_bit(_ir_decode_data.flags, UNIQUE_FOOTER) == 1)
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
            
            
            
        }else if((get_bit(_ir_decode_data.flags, NEC_FOOTER) == 0) && 
                (get_bit(_ir_decode_data.flags, UNIQUE_FOOTER) == 0)) 
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
            if(get_bit(_ir_decode_data.flags, REPEAT) == 0)
            {
                can_send_hex_value(_ir_decode_data, &seq_no, *communication_id, 1);    
            }
        }
        
        else if(_temp_packet_count == 3)
        {
            if(get_bit(_ir_decode_data.flags, REPEAT) == 0)
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

void print_can_message(unsigned char *_can_message)
{
    printf("CAN Message : %d | %2x %2x %2x %2x %2x %2x %2x %2x\n", 
            _can_message[0], _can_message[0], _can_message[1], _can_message[2], _can_message[3],
            _can_message[4], _can_message[5], _can_message[6], _can_message[7]);
}

void generate_rcv_can_message()
{
    init_decode_data(&received_ir_decoded_data);

    unsigned char can_message[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    // 1st CAN packet
    can_message[0] = 0x01;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x09;      // remote id 0
    can_message[3] = 0xAC;      // remote id 1
    can_message[4] = 0x23;      // remote id 2
    can_message[5] = 0x17;      // cmd
    can_message[6] = 0x81;      // hdr_mark lsb
    can_message[7] = 0x24;      // hdr_mark msb

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);

    // 2nd CAN packet
    can_message[0] = 0x02;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0xd7;      // hdr_space lsb
    can_message[3] = 0x11;      // hdr_space msb
    can_message[4] = 0x3C;      // bit_mark lsb
    can_message[5] = 0x02;      // bit_mark msb
    can_message[6] = 0x2F;      // zero_space lsb
    can_message[7] = 0x02;      // zero_space msb

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);

    // 3rd CAN packet
    can_message[0] = 0x03;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x9b;      // one_space lsb
    can_message[3] = 0x06;      // one_space msb
    can_message[4] = 0b00000011;// flags
    can_message[5] = 0xA0;      // bits[0]
    can_message[6] = 0x90;      // bits[1]
    can_message[7] = 0x00;      // bits[2]

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);

    // 4th CAN packet
    can_message[0] = 0x04;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x39;      // gap lsb
    can_message[3] = 0x2F;      // gap msb
    can_message[4] = 0x29;      // ftr_space lsb
    can_message[5] = 0x09;      // ftr_space msb
    can_message[6] = 0xAF;      // ftr_mark lsb
    can_message[7] = 0x1C;      // ftr_mark msb

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);

    // 5th CAN packet - Hex value
    can_message[0] = 0x05;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x87;      // hex_value[0].first 0 lsb
    can_message[3] = 0x39;      // hex_value[0].first 1
    can_message[4] = 0x00;      // hex_value[0].first 2
    can_message[5] = 0x00;      // hex_value[0].first 3 
    can_message[6] = 0x00;      // hex_value[0].first 4 
    can_message[7] = 0x00;      // hex_value[0].first 5

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);

    // 6th CAN packet - Hex value
    can_message[0] = 0x06;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x00;      // hex_value[0].first 6 
    can_message[3] = 0xA0;      // hex_value[0].first 7 msb
    can_message[4] = 0x00;      // hex_value[0].second 0 lsb
    can_message[5] = 0x00;      // hex_value[0].second 1 
    can_message[6] = 0x00;      // hex_value[0].second 2 
    can_message[7] = 0x00;      // hex_value[0].second 3

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);

    // 7th CAN packet - Hex value
    can_message[0] = 0x07;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x00;      // hex_value[0].second 4 
    can_message[3] = 0x00;      // hex_value[0].second 5
    can_message[4] = 0x00;      // hex_value[0].second 6 
    can_message[5] = 0xB0;      // hex_value[0].second 7 msb 
    can_message[6] = 0x00;      // hex_value[0].third 0 lsb 
    can_message[7] = 0x00;      // hex_value[0].third 1

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);

    // 8th CAN packet - Hex value
    can_message[0] = 0x08;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x00;      // hex_value[0].third 2 
    can_message[3] = 0xE0;      // hex_value[0].third 3
    can_message[4] = 0x00;      // hex_value[0].third 4 
    can_message[5] = 0x00;      // hex_value[0].third 5 
    can_message[6] = 0x00;      // hex_value[0].third 6 
    can_message[7] = 0x00;      // hex_value[0].third 7 msb

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);


    // 9th CAN packet - Hex value
    can_message[0] = 0x09;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x87;      // hex_value[1].first 0 lsb
    can_message[3] = 0xA9;      // hex_value[1].first 1
    can_message[4] = 0x00;      // hex_value[1].first 2
    can_message[5] = 0x00;      // hex_value[1].first 3 
    can_message[6] = 0x00;      // hex_value[1].first 4 
    can_message[7] = 0x00;      // hex_value[1].first 5

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);

    // 10th CAN packet - Hex value
    can_message[0] = 0x0A;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x00;      // hex_value[1].first 6 
    can_message[3] = 0x00;      // hex_value[1].first 7 msb
    can_message[4] = 0x00;      // hex_value[1].second 0 lsb
    can_message[5] = 0x00;      // hex_value[1].second 1 
    can_message[6] = 0x00;      // hex_value[1].second 2 
    can_message[7] = 0x00;      // hex_value[1].second 3

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);

    // 11th CAN packet - Hex value
    can_message[0] = 0x0B;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x00;      // hex_value[1].second 4 
    can_message[3] = 0x00;      // hex_value[1].second 5
    can_message[4] = 0x00;      // hex_value[1].second 6 
    can_message[5] = 0x00;      // hex_value[1].second 7 msb 
    can_message[6] = 0x00;      // hex_value[1].third 0 lsb 
    can_message[7] = 0xF0;      // hex_value[1].third 1

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);


    // 12th CAN packet - Hex value
    can_message[0] = 0x0C;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x00;      // hex_value[1].third 2 
    can_message[3] = 0x00;      // hex_value[1].third 3
    can_message[4] = 0x00;      // hex_value[1].third 4 
    can_message[5] = 0x00;      // hex_value[1].third 5 
    can_message[6] = 0x00;      // hex_value[1].third 6 
    can_message[7] = 0x00;      // hex_value[1].third 7 msb

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);



    // 13th CAN packet - Hex value
    can_message[0] = 0x0D;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x87;      // hex_value[1].first 0 lsb
    can_message[3] = 0xB9;      // hex_value[1].first 1
    can_message[4] = 0x00;      // hex_value[1].first 2
    can_message[5] = 0x00;      // hex_value[1].first 3 
    can_message[6] = 0x00;      // hex_value[1].first 4 
    can_message[7] = 0x00;      // hex_value[1].first 5

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);

    // 14th CAN packet - Hex value
    can_message[0] = 0x0E;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x00;      // hex_value[1].first 6 
    can_message[3] = 0x00;      // hex_value[1].first 7 msb
    can_message[4] = 0x00;      // hex_value[1].second 0 lsb
    can_message[5] = 0x00;      // hex_value[1].second 1 
    can_message[6] = 0x00;      // hex_value[1].second 2 
    can_message[7] = 0x00;      // hex_value[1].second 3

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);

    // 15th CAN packet - Hex value
    can_message[0] = 0x0F;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x00;      // hex_value[1].second 4 
    can_message[3] = 0x00;      // hex_value[1].second 5
    can_message[4] = 0x00;      // hex_value[1].second 6 
    can_message[5] = 0x00;      // hex_value[1].second 7 msb 
    can_message[6] = 0x00;      // hex_value[1].third 0 lsb 
    can_message[7] = 0x00;      // hex_value[1].third 1

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);


    // 16th CAN packet - Hex value
    can_message[0] = 0x10;      // seq no
    can_message[1] = 0x7A;      // communication if
    can_message[2] = 0x00;      // hex_value[1].third 2 
    can_message[3] = 0x00;      // hex_value[1].third 3
    can_message[4] = 0x00;      // hex_value[1].third 4 
    can_message[5] = 0x00;      // hex_value[1].third 5 
    can_message[6] = 0x00;      // hex_value[1].third 6 
    can_message[7] = 0x00;      // hex_value[1].third 7 msb

    print_can_message(can_message);
    ir_rd_packet_handler(can_message);

    print_decode_data(&received_ir_decoded_data);
    generate_ir_signal();
}

void ir_rd_packet_handler(unsigned char *_can_message)
{
    uint8_t seq_no = 0;
    uint8_t communication_id = 0;
    uint8_t data[6] = {0, 0, 0, 0, 0, 0};

    seq_no = _can_message[0];
    communication_id = _can_message[1];

    for(int i = 0; i < 6; i++)
    {
        data[i] = _can_message[i + 2];
    }

    ir_rd_data_packet(&seq_no, data, &communication_id);
}

void ir_rd_data_packet(uint8_t *_seq_no, uint8_t *_data, uint8_t *communication_id)
{
    /*
        this method isn't match for the MCU,
        MCU need different approch
    */
    if(*_seq_no == 1)
    {
        printf("Sequence %d received\n", *_seq_no);
        received_ir_decoded_data.hdr_mark = ((_data[5] << 8) | (_data[4] << 0));
    }

    if(*_seq_no == 2)
    {
        printf("Sequence %d received\n", *_seq_no);
        received_ir_decoded_data.hdr_space  = ((_data[1] << 8) | (_data[0] << 0));
        received_ir_decoded_data.bit_mark   = ((_data[3] << 8) | (_data[2] << 0));
        received_ir_decoded_data.zero_space = ((_data[5] << 8) | (_data[4] << 0));
    }

    if(*_seq_no == 3)
    {
        int _temp_secection_count = 0;
        printf("Sequence %d received\n", *_seq_no);
        received_ir_decoded_data.one_space  = ((_data[1] << 8) | (_data[0] << 0));
        received_ir_decoded_data.flags      = _data[2];
        received_ir_decoded_data.bits[0]    = _data[3];
        received_ir_decoded_data.bits[1]    = _data[4];
        received_ir_decoded_data.bits[2]    = _data[5];

        // get number of sections in ir signal
        _temp_secection_count = section_count();

        if(get_bit((received_ir_decoded_data.flags), REPEAT) == 1)
        {
            received_ir_decoded_data.repeat = _temp_secection_count;
        }
        else
        {
            received_ir_decoded_data.repeat = 0;
        }
    }

    if(*_seq_no == 4)
    {
        printf("Sequence %d received\n", *_seq_no);
        received_ir_decoded_data.gap        = ((_data[1] << 8) | (_data[0] << 0));
        received_ir_decoded_data.ftr_space  = ((_data[3] << 8) | (_data[2] << 0));
        received_ir_decoded_data.ftr_mark   = ((_data[5] << 8) | (_data[4] << 0));
    }

    if(*_seq_no == 5)
    {   
        unsigned long long int _temp_hex_first = 0;
        unsigned long long int _temp_data = 0;

        printf("Sequence %d received\n", *_seq_no);

        for(int i = 0; i < 6; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_first = _temp_hex_first | _temp_data << (i * 8);
        }
        received_ir_decoded_data.decoded_val[0].first = received_ir_decoded_data.decoded_val[0].first | _temp_hex_first;
    }

    if(*_seq_no == 6)
    {   
        unsigned long long _temp_hex_first = 0;
        unsigned long long _temp_hex_second = 0;
        unsigned long long int _temp_data = 0;

        printf("Sequence %d received\n", *_seq_no);
        
        // _temp_hex_first = ((_data[0] << 48) | (_data[1] << 56));
        for(int i = 0; i < 2; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_first = _temp_hex_first | _temp_data << ((i + 6) * 8);
        }
        received_ir_decoded_data.decoded_val[0].first = received_ir_decoded_data.decoded_val[0].first | _temp_hex_first;


        // _temp_hex_second = ((_data[2] << 0) | (_data[3] << 8) 
        //                     | (_data[4] << 16) | (_data[5] << 24));
        // received_ir_decoded_data.decoded_val[0].second = received_ir_decoded_data.decoded_val[0].second | _temp_hex_second;
        for(int i = 2; i < 6; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_second = _temp_hex_second | _temp_data << ((i - 2) * 8);
        }
        received_ir_decoded_data.decoded_val[0].second = received_ir_decoded_data.decoded_val[0].second | _temp_hex_second;
    }

    if(*_seq_no == 7)
    {           
        unsigned long long _temp_hex_second = 0;
        unsigned long long _temp_hex_third = 0;
        unsigned long long int _temp_data = 0;

        printf("Sequence %d received\n", *_seq_no);
        // _temp_hex_second = ((_data[0] << 32) | (_data[1] << 40) 
        //                     | (_data[2] << 48) | (_data[3] << 56));
        // received_ir_decoded_data.decoded_val[0].second = received_ir_decoded_data.decoded_val[0].second | _temp_hex_second;
        for(int i = 0; i < 4; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_second = _temp_hex_second | _temp_data << ((i + 4) * 8);
        }
        received_ir_decoded_data.decoded_val[0].second = received_ir_decoded_data.decoded_val[0].second | _temp_hex_second;

        // _temp_hex_third = ((_data[4] << 0) | (_data[5] << 8));
        // received_ir_decoded_data.decoded_val[0].third = received_ir_decoded_data.decoded_val[0].third | _temp_hex_third;
        for(int i = 4; i < 6; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_third = _temp_hex_third | _temp_data << ((i - 4) * 8);
        }
        received_ir_decoded_data.decoded_val[0].third = received_ir_decoded_data.decoded_val[0].third | _temp_hex_third;
    }

    if(*_seq_no == 8)
    {   
        unsigned long long _temp_hex_third = 0;
        unsigned long long int _temp_data = 0;
        printf("Sequence %d received\n", *_seq_no);

        // _temp_hex_third = ((_data[0] << 16) | (_data[1] << 24) | (_data[2] << 32) 
        //                     | (_data[3] << 40)| (_data[4] << 48) | (_data[5] << 56));

        // received_ir_decoded_data.decoded_val[0].third = received_ir_decoded_data.decoded_val[0].third | _temp_hex_third;
        for(int i = 0; i < 6; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_third = _temp_hex_third | _temp_data << ((i + 2) * 8);
        }
        received_ir_decoded_data.decoded_val[0].third = received_ir_decoded_data.decoded_val[0].third | _temp_hex_third;

    }

    if(*_seq_no == 9)
    {   
        unsigned long long int _temp_hex_first = 0;
        unsigned long long int _temp_data = 0;

        printf("Sequence %d received\n", *_seq_no);

        for(int i = 0; i < 6; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_first = _temp_hex_first | _temp_data << (i * 8);
        }
        received_ir_decoded_data.decoded_val[1].first = received_ir_decoded_data.decoded_val[1].first | _temp_hex_first;
    }

    if(*_seq_no == 10)
    {   
        unsigned long long _temp_hex_first = 0;
        unsigned long long _temp_hex_second = 0;
        unsigned long long int _temp_data = 0;

        printf("Sequence %d received\n", *_seq_no);
        
        for(int i = 0; i < 2; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_first = _temp_hex_first | _temp_data << ((i + 6) * 8);
        }
        received_ir_decoded_data.decoded_val[1].first = received_ir_decoded_data.decoded_val[1].first | _temp_hex_first;

        for(int i = 2; i < 6; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_second = _temp_hex_second | _temp_data << ((i - 2) * 8);
        }
        received_ir_decoded_data.decoded_val[1].second = received_ir_decoded_data.decoded_val[1].second | _temp_hex_second;
    }

    if(*_seq_no == 11)
    {           
        unsigned long long _temp_hex_second = 0;
        unsigned long long _temp_hex_third = 0;
        unsigned long long int _temp_data = 0;

        printf("Sequence %d received\n", *_seq_no);
        
        for(int i = 0; i < 4; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_second = _temp_hex_second | _temp_data << ((i + 4) * 8);
        }
        received_ir_decoded_data.decoded_val[1].second = received_ir_decoded_data.decoded_val[1].second | _temp_hex_second;

        for(int i = 4; i < 6; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_third = _temp_hex_third | _temp_data << ((i - 4) * 8);
        }
        received_ir_decoded_data.decoded_val[1].third = received_ir_decoded_data.decoded_val[1].third | _temp_hex_third;
    }

    if(*_seq_no == 12)
    {   
        unsigned long long _temp_hex_third = 0;
        unsigned long long int _temp_data = 0;
        printf("Sequence %d received\n", *_seq_no);

        for(int i = 0; i < 6; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_third = _temp_hex_third | _temp_data << ((i + 2) * 8);
        }
        received_ir_decoded_data.decoded_val[1].third = received_ir_decoded_data.decoded_val[1].third | _temp_hex_third;
    }

    if(*_seq_no == 13)
    {   
        unsigned long long int _temp_hex_first = 0;
        unsigned long long int _temp_data = 0;

        printf("Sequence %d received\n", *_seq_no);

        for(int i = 0; i < 6; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_first = _temp_hex_first | _temp_data << (i * 8);
        }
        received_ir_decoded_data.decoded_val[2].first = received_ir_decoded_data.decoded_val[2].first | _temp_hex_first;
    }

    if(*_seq_no == 14)
    {   
        unsigned long long _temp_hex_first = 0;
        unsigned long long _temp_hex_second = 0;
        unsigned long long int _temp_data = 0;

        printf("Sequence %d received\n", *_seq_no);
        
        for(int i = 0; i < 2; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_first = _temp_hex_first | _temp_data << ((i + 6) * 8);
        }
        received_ir_decoded_data.decoded_val[2].first = received_ir_decoded_data.decoded_val[2].first | _temp_hex_first;

        for(int i = 2; i < 6; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_second = _temp_hex_second | _temp_data << ((i - 2) * 8);
        }
        received_ir_decoded_data.decoded_val[2].second = received_ir_decoded_data.decoded_val[2].second | _temp_hex_second;
    }

    if(*_seq_no == 15)
    {           
        unsigned long long _temp_hex_second = 0;
        unsigned long long _temp_hex_third = 0;
        unsigned long long int _temp_data = 0;

        printf("Sequence %d received\n", *_seq_no);
        
        for(int i = 0; i < 4; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_second = _temp_hex_second | _temp_data << ((i + 4) * 8);
        }
        received_ir_decoded_data.decoded_val[2].second = received_ir_decoded_data.decoded_val[2].second | _temp_hex_second;

        for(int i = 4; i < 6; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_third = _temp_hex_third | _temp_data << ((i - 4) * 8);
        }
        received_ir_decoded_data.decoded_val[2].third = received_ir_decoded_data.decoded_val[2].third | _temp_hex_third;
    }

    if(*_seq_no == 16)
    {   
        unsigned long long _temp_hex_third = 0;
        unsigned long long int _temp_data = 0;
        printf("Sequence %d received\n", *_seq_no);

        for(int i = 0; i < 6; i ++)
        {
            _temp_data = _data[i];
            _temp_hex_third = _temp_hex_third | _temp_data << ((i + 2) * 8);
        }
        received_ir_decoded_data.decoded_val[2].third = received_ir_decoded_data.decoded_val[2].third | _temp_hex_third;
    }
}


void generate_ir_signal()
{
    int16_t bit_count = 0;
    int data_buf_counter = 0;
    int temp_count = 0;
    int temp_section_count = 0;

    bit_count = calc_bit_count();
    printf("Needed Bit Count : %d\n", bit_count);

    temp_section_count = section_count();
    printf("Section Count : %d\n", temp_section_count);

    uint16_t *generated_ir_buf = new uint16_t[bit_count];


    generated_ir_buf[data_buf_counter++] = received_ir_decoded_data.hdr_mark;
    generated_ir_buf[data_buf_counter++] = received_ir_decoded_data.hdr_space;

    
    if(temp_section_count == 1)
    {
        // one section available with/ without footer
        // generate 1st packet
        gen_ir_pattern_single_section(received_ir_decoded_data.bits[0], 
                                        received_ir_decoded_data.decoded_val[0],
                                        &data_buf_counter,
                                        generated_ir_buf);

        // check if there is a footer
        if ((get_bit(received_ir_decoded_data.flags, NEC_FOOTER) == 1) || 
            (get_bit(received_ir_decoded_data.flags, UNIQUE_FOOTER) == 1))
        {
            bool _temp_is_nec = false;
            _temp_is_nec = (get_bit(received_ir_decoded_data.flags, NEC_FOOTER) == 1) ? true : false;
            gen_ir_footer(&data_buf_counter, generated_ir_buf, _temp_is_nec);
        }

        // generate end
        gen_ir_end(&data_buf_counter, generated_ir_buf);

        // print buffer
        print_ir_buffer(generated_ir_buf, data_buf_counter);
    }
    
    else if(temp_section_count == 2)
    {
        // two sections available with/without repeat and with/without footer

        // generate 1st packet
        gen_ir_pattern_single_section(received_ir_decoded_data.bits[0], 
                                        received_ir_decoded_data.decoded_val[0],
                                        &data_buf_counter,
                                        generated_ir_buf);
        
        // generate the gap between packets
        gen_ir_gap(&data_buf_counter, generated_ir_buf);

        // check if there is a repeat
        if(get_bit(received_ir_decoded_data.flags, REPEAT) == 1)
        {
            // generate the 2nd packet as a repeat
            gen_ir_pattern_single_section(received_ir_decoded_data.bits[0], 
                                        received_ir_decoded_data.decoded_val[0],
                                        &data_buf_counter,
                                        generated_ir_buf);
        }
        else
        {
            // no-repreat; generate 2nd packet
            gen_ir_pattern_single_section(received_ir_decoded_data.bits[1], 
                                        received_ir_decoded_data.decoded_val[1],
                                        &data_buf_counter,
                                        generated_ir_buf);
        }

        // check if there is a footer
        if ((get_bit(received_ir_decoded_data.flags, NEC_FOOTER) == 1) || 
            (get_bit(received_ir_decoded_data.flags, UNIQUE_FOOTER) == 1))
        {
            bool _temp_is_nec = false;
            _temp_is_nec = (get_bit(received_ir_decoded_data.flags, NEC_FOOTER) == 1) ? true : false;
            gen_ir_footer(&data_buf_counter, generated_ir_buf, _temp_is_nec);
        }

        // generate end
        gen_ir_end(&data_buf_counter, generated_ir_buf);
        
        // print ir sigal array
        print_ir_buffer(generated_ir_buf, data_buf_counter);
        
    }

    else if(temp_section_count == 3)
    {
        // three sections available with/without repeat and without footer

        // generate 1st packet
        gen_ir_pattern_single_section(received_ir_decoded_data.bits[0], 
                                        received_ir_decoded_data.decoded_val[0],
                                        &data_buf_counter,
                                        generated_ir_buf);
        
        // generate the gap between packets
        gen_ir_gap(&data_buf_counter, generated_ir_buf);

        // check if there is a repeat
        if(get_bit(received_ir_decoded_data.flags, REPEAT) == 1)
        {
            // generate the 2nd packet as a repeat 
            gen_ir_pattern_single_section(received_ir_decoded_data.bits[0], 
                                        received_ir_decoded_data.decoded_val[0],
                                        &data_buf_counter,
                                        generated_ir_buf);
        
            gen_ir_gap(&data_buf_counter, generated_ir_buf);

            // generate the 3rd packet as a repeat 
            gen_ir_pattern_single_section(received_ir_decoded_data.bits[0], 
                                        received_ir_decoded_data.decoded_val[0],
                                        &data_buf_counter,
                                        generated_ir_buf);
            
        }
        else
        {
            // no-repreat; generate 2nd packet
            gen_ir_pattern_single_section(received_ir_decoded_data.bits[1], 
                                        received_ir_decoded_data.decoded_val[1],
                                        &data_buf_counter,
                                        generated_ir_buf);
                
            gen_ir_gap(&data_buf_counter, generated_ir_buf);

            // no-repreat; generate 3rd packet
            gen_ir_pattern_single_section(received_ir_decoded_data.bits[2], 
                                        received_ir_decoded_data.decoded_val[2],
                                        &data_buf_counter,
                                        generated_ir_buf);

        }

        // check if there is a footer
        if ((get_bit(received_ir_decoded_data.flags, NEC_FOOTER) == 1) || 
            (get_bit(received_ir_decoded_data.flags, UNIQUE_FOOTER) == 1))
        {
            bool _temp_is_nec = false;
            _temp_is_nec = (get_bit(received_ir_decoded_data.flags, NEC_FOOTER) == 1) ? true : false;
            gen_ir_footer(&data_buf_counter, generated_ir_buf, _temp_is_nec);
        }

        // generate end
        gen_ir_end(&data_buf_counter, generated_ir_buf);

        // print ir sigal array
        print_ir_buffer(generated_ir_buf, data_buf_counter);
    }

}

void gen_ir_pattern_single_section(uint8_t _bits, ir_val_hex_t _decoded_val, int* _buf_counter, uint16_t *_ir_buf)
{
    int temp_count = 0;
    int temp_buf_counter = 0;

    temp_buf_counter = *_buf_counter;

    for(int i = 0; i < _bits; i++)
    {
        if(i < 64)
        {
            if((_decoded_val.first & (1ull << temp_count)) >> temp_count)
            {
                _ir_buf[temp_buf_counter++] = received_ir_decoded_data.bit_mark;
                _ir_buf[temp_buf_counter++] = received_ir_decoded_data.one_space;
            }
            else
            {
                _ir_buf[temp_buf_counter++] = received_ir_decoded_data.bit_mark;
                _ir_buf[temp_buf_counter++] = received_ir_decoded_data.zero_space;
            }
        }
        else if(i < 128)
        {
            if((_decoded_val.second & (1ull << (temp_count - 64))) >> (temp_count - 64))
            {
                _ir_buf[temp_buf_counter++] = received_ir_decoded_data.bit_mark;
                _ir_buf[temp_buf_counter++] = received_ir_decoded_data.one_space;
            }
            else
            {
                _ir_buf[temp_buf_counter++] = received_ir_decoded_data.bit_mark;
                _ir_buf[temp_buf_counter++] = received_ir_decoded_data.zero_space;
            }
        }
        else
        {
            if((_decoded_val.third & (1ull << (temp_count - 128))) >> (temp_count - 128))
            {
                _ir_buf[temp_buf_counter++] = received_ir_decoded_data.bit_mark;
                _ir_buf[temp_buf_counter++] = received_ir_decoded_data.one_space;
            }
            else
            {
                _ir_buf[temp_buf_counter++] = received_ir_decoded_data.bit_mark;
                _ir_buf[temp_buf_counter++] = received_ir_decoded_data.zero_space;
            }
        }

	    temp_count ++;
    }

    *_buf_counter = temp_buf_counter;
}

void gen_ir_gap(int *_buf_counter, uint16_t *_ir_buf)
{
    int temp_buf_counter = 0;
    temp_buf_counter = *_buf_counter;

    _ir_buf[temp_buf_counter++] = received_ir_decoded_data.bit_mark;
    _ir_buf[temp_buf_counter++] = received_ir_decoded_data.gap;
    _ir_buf[temp_buf_counter++] = received_ir_decoded_data.hdr_mark;
    _ir_buf[temp_buf_counter++] = received_ir_decoded_data.hdr_space;

    *_buf_counter = temp_buf_counter;
}

void gen_ir_end(int *_buf_counter, uint16_t *_ir_buf)
{
    int temp_buf_counter = 0;
    temp_buf_counter = *_buf_counter;

    _ir_buf[temp_buf_counter++] = received_ir_decoded_data.bit_mark;
    _ir_buf[temp_buf_counter++] = IR_END_SPACE;

    *_buf_counter = temp_buf_counter;
}

void gen_ir_footer(int *_buf_counter, uint16_t *_ir_buf, bool is_nec)
{
    int temp_buf_counter = 0;
    temp_buf_counter = *_buf_counter;

    _ir_buf[temp_buf_counter++] = received_ir_decoded_data.bit_mark;
    _ir_buf[temp_buf_counter++] = received_ir_decoded_data.gap;

    if(is_nec)
    {
        // this is NEC footer; footer mark = header mark
        _ir_buf[temp_buf_counter++] = received_ir_decoded_data.hdr_mark;
    }
    else
    {
        // unique footer
        _ir_buf[temp_buf_counter++] = received_ir_decoded_data.ftr_mark;
    }

    _ir_buf[temp_buf_counter++] = received_ir_decoded_data.ftr_space;

    *_buf_counter = temp_buf_counter;
}

int16_t calc_bit_count()
{
    int16_t bit_count = 0;
    int _temp_section_count = 0;

    _temp_section_count = get_bit(received_ir_decoded_data.flags, FIRST_PACKET)
                            + get_bit(received_ir_decoded_data.flags, SECOND_PACKET)
                            + get_bit(received_ir_decoded_data.flags, THIRD_PACKET);

    if((get_bit(received_ir_decoded_data.flags, NEC_FOOTER) == 0) && 
        (get_bit(received_ir_decoded_data.flags, UNIQUE_FOOTER) == 0))
    {
        // no footer available
        // printf("No Footer available\n");

        if(_temp_section_count == 1)
        {
            // 1 section with no footer
            bit_count = IR_HEADER_LENGTH + 
                        (received_ir_decoded_data.bits[0] * 2) + 
                        IR_END_LENGTH;
        }
        else if(_temp_section_count == 2)
        {
            if(get_bit(received_ir_decoded_data.flags, REPEAT) == 1)
            {
                // 2 sections with repeat and without footer
                bit_count = IR_HEADER_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_GAP_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_END_LENGTH;
            }
            else
            {
                // 2 sections without repeat and without footer
                bit_count = IR_HEADER_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_GAP_LENGTH + 
                            (received_ir_decoded_data.bits[1] * 2) +
                            IR_END_LENGTH;
            }
        }

        else if(_temp_section_count == 3)
        {
            if(get_bit(received_ir_decoded_data.flags, REPEAT) == 1)
            {
                // 3 sections with repeat and without footer
                bit_count = IR_HEADER_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_GAP_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_GAP_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_END_LENGTH;
            }
            else
            {
                // 3 sections without repeat and without footer
                bit_count = IR_HEADER_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_GAP_LENGTH + 
                            (received_ir_decoded_data.bits[1] * 2) +
                            IR_GAP_LENGTH + 
                            (received_ir_decoded_data.bits[1] * 2) +
                            IR_END_LENGTH;
            }
        }
    }
    else if((get_bit(received_ir_decoded_data.flags, NEC_FOOTER) == 1) ||
             (get_bit(received_ir_decoded_data.flags, UNIQUE_FOOTER) == 1))
    {
        // NEC footer available
        // printf("NEC or Unique Footer available\n");

        if(_temp_section_count == 1)
        {
            // 1 section with footer
            bit_count = IR_HEADER_LENGTH + 
                        (received_ir_decoded_data.bits[0] * 2) + 
                        IR_FOOTER_LENGTH + 
                        IR_END_LENGTH;
        }
        else if(_temp_section_count == 2)
        {
            if(get_bit(received_ir_decoded_data.flags, REPEAT) == 1)
            {
                // 2 sections with repeat and with footer
                bit_count = IR_HEADER_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_GAP_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_FOOTER_LENGTH + 
                            IR_END_LENGTH;
            }
            else
            {
                // 2 sections without repeat and with footer
                bit_count = IR_HEADER_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_GAP_LENGTH + 
                            (received_ir_decoded_data.bits[1] * 2) +
                            IR_FOOTER_LENGTH + 
                            IR_END_LENGTH;
            }
        }

        else if(_temp_section_count == 3)
        {
            if(get_bit(received_ir_decoded_data.flags, REPEAT) == 1)
            {
                // 3 sections with repeat and with footer
                bit_count = IR_HEADER_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_GAP_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_GAP_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_FOOTER_LENGTH + 
                            IR_END_LENGTH;
            }
            else
            {
                // 3 sections without repeat and with footer
                bit_count = IR_HEADER_LENGTH + 
                            (received_ir_decoded_data.bits[0] * 2) +
                            IR_GAP_LENGTH + 
                            (received_ir_decoded_data.bits[1] * 2) +
                            IR_GAP_LENGTH + 
                            (received_ir_decoded_data.bits[1] * 2) +
                            IR_FOOTER_LENGTH + 
                            IR_END_LENGTH;
            }
        }
    }

    return bit_count;
}

int section_count()
{
    int _temp_section_count = 0;
    _temp_section_count = get_bit(received_ir_decoded_data.flags, FIRST_PACKET)
                            + get_bit(received_ir_decoded_data.flags, SECOND_PACKET)
                            + get_bit(received_ir_decoded_data.flags, THIRD_PACKET);

    return _temp_section_count;
}


void print_ir_buffer(uint16_t *_buf, int16_t size_buf)
{
    for(int i = 0; i < size_buf; i++)
    {
        if((i > 0) && ((i % 10) == 0))
        {
            printf("\n");
        }
        printf("%d, ", _buf[i]);
    }
    
    printf("\n");
}