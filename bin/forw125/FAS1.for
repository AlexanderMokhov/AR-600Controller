      SUBROUTINE SH0054                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  487))                                             
      EQUIVALENCE(EM0011,GR(  488))                                             
      EQUIVALENCE(EM0012,GR(  489))                                             
      EQUIVALENCE(EM0013,GR(  490))                                             
      EQUIVALENCE(EM0014,GR(  491))                                             
      EQUIVALENCE(EM0015,GR(  492))                                             
      EQUIVALENCE(EM0016,GR(  493))                                             
      EQUIVALENCE(EM0017,GR(  494))                                             
      EQUIVALENCE(EM0018,GR(  495))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  286))                                             
      EQUIVALENCE(EM0025,GR(  287))                                             
      EQUIVALENCE(EM0020,GR(  288))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(  121))                                             
      EQUIVALENCE(EM0029,GR(  122))                                             
      EQUIVALENCE(EM0030,GR(  123))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  283))                                             
      EQUIVALENCE(EM0032,GR(  284))                                             
      EQUIVALENCE(EM0033,GR(  285))                                             
      EQUIVALENCE(EM0034,GR(  286))                                             
      EQUIVALENCE(EM0035,GR(  287))                                             
      EQUIVALENCE(EM0036,GR(  288))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  408))                                             
      EQUIVALENCE(EM0038,GV(  401))                                             
      EQUIVALENCE(EM0039,GV(  400))                                             
C +EM0037+EM0038+EM0039                                                         
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  504))                                             
      EQUIVALENCE(EM0041,GR(  505))                                             
      EQUIVALENCE(EM0042,GR(  506))                                             
      EQUIVALENCE(EM0043,GR(  507))                                             
      EQUIVALENCE(EM0044,GR(  508))                                             
      EQUIVALENCE(EM0045,GR(  509))                                             
      EQUIVALENCE(EM0046,GR(  510))                                             
      EQUIVALENCE(EM0047,GR(  511))                                             
      EQUIVALENCE(EM0048,GR(  512))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  292))                                             
      EQUIVALENCE(EM0055,GR(  293))                                             
      EQUIVALENCE(EM0050,GR(  294))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(  127))                                             
      EQUIVALENCE(EM0059,GR(  128))                                             
      EQUIVALENCE(EM0060,GR(  129))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  289))                                             
      EQUIVALENCE(EM0062,GR(  290))                                             
      EQUIVALENCE(EM0063,GR(  291))                                             
      EQUIVALENCE(EM0064,GR(  292))                                             
      EQUIVALENCE(EM0065,GR(  293))                                             
      EQUIVALENCE(EM0066,GR(  294))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  416))                                             
      EQUIVALENCE(EM0068,GV(  413))                                             
      EQUIVALENCE(EM0069,GV(  412))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0130,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  163)=+EM0085                                                          
      A(  164)=+EM0088                                                          
      A(  165)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  166)=+EM0104                                                          
      A(  167)=+EM0105                                                          
      A(  168)=-EM0085                                                          
      A(  169)=-EM0088                                                          
      A(  170)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  171)=-EM0106                                                          
      A(  172)=-EM0107                                                          
      A(  173)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(    1)=+EM0127                                                          
      SL(    1)=-EM0082                                                         
      A(  174)=+EM0087                                                          
      A(  175)=+EM0090                                                          
      A(  176)=+EM0093                                                          
      EM0131=                                   -EM0037                         
      A(  177)=+EM0130                                                          
      A(  178)=+EM0131                                                          
      A(  179)=-EM0087                                                          
      A(  180)=-EM0090                                                          
      A(  181)=-EM0093                                                          
      EM0133=              +EM0102*EM0068-EM0099*EM0069                         
      EM0134=              +EM0096*EM0069-EM0102*EM0067                         
      EM0135=              +EM0099*EM0067-EM0096*EM0068                         
      A(  182)=-EM0133                                                          
      A(  183)=-EM0134                                                          
      A(  184)=-EM0135                                                          
      B(    2)=+EM0129                                                          
      SL(    2)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0053                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  487))                                             
      EQUIVALENCE(EM0011,GR(  488))                                             
      EQUIVALENCE(EM0012,GR(  489))                                             
      EQUIVALENCE(EM0013,GR(  490))                                             
      EQUIVALENCE(EM0014,GR(  491))                                             
      EQUIVALENCE(EM0015,GR(  492))                                             
      EQUIVALENCE(EM0016,GR(  493))                                             
      EQUIVALENCE(EM0017,GR(  494))                                             
      EQUIVALENCE(EM0018,GR(  495))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  286))                                             
      EQUIVALENCE(EM0025,GR(  287))                                             
      EQUIVALENCE(EM0020,GR(  288))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(  121))                                             
      EQUIVALENCE(EM0029,GR(  122))                                             
      EQUIVALENCE(EM0030,GR(  123))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  283))                                             
      EQUIVALENCE(EM0032,GR(  284))                                             
      EQUIVALENCE(EM0033,GR(  285))                                             
      EQUIVALENCE(EM0034,GR(  286))                                             
      EQUIVALENCE(EM0035,GR(  287))                                             
      EQUIVALENCE(EM0036,GR(  288))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  409))                                             
      EQUIVALENCE(EM0038,GV(  403))                                             
      EQUIVALENCE(EM0039,GV(  402))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  504))                                             
      EQUIVALENCE(EM0041,GR(  505))                                             
      EQUIVALENCE(EM0042,GR(  506))                                             
      EQUIVALENCE(EM0043,GR(  507))                                             
      EQUIVALENCE(EM0044,GR(  508))                                             
      EQUIVALENCE(EM0045,GR(  509))                                             
      EQUIVALENCE(EM0046,GR(  510))                                             
      EQUIVALENCE(EM0047,GR(  511))                                             
      EQUIVALENCE(EM0048,GR(  512))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  292))                                             
      EQUIVALENCE(EM0055,GR(  293))                                             
      EQUIVALENCE(EM0050,GR(  294))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(  127))                                             
      EQUIVALENCE(EM0059,GR(  128))                                             
      EQUIVALENCE(EM0060,GR(  129))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  289))                                             
      EQUIVALENCE(EM0062,GR(  290))                                             
      EQUIVALENCE(EM0063,GR(  291))                                             
      EQUIVALENCE(EM0064,GR(  292))                                             
      EQUIVALENCE(EM0065,GR(  293))                                             
      EQUIVALENCE(EM0066,GR(  294))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  417))                                             
      EQUIVALENCE(EM0068,GV(  415))                                             
      EQUIVALENCE(EM0069,GV(  414))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
      EQUIVALENCE(EM0136,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  185)=+EM0085                                                          
      A(  186)=+EM0088                                                          
      A(  187)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  188)=+EM0104                                                          
      A(  189)=+EM0105                                                          
      A(  190)=-EM0085                                                          
      A(  191)=-EM0088                                                          
      A(  192)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  193)=-EM0106                                                          
      A(  194)=-EM0107                                                          
      A(  195)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(    3)=+EM0127                                                          
      SL(    3)=-EM0082                                                         
      A(  196)=+EM0086                                                          
      A(  197)=+EM0089                                                          
      A(  198)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  199)=+EM0130                                                          
      A(  200)=+EM0132                                                          
      A(  201)=-EM0086                                                          
      A(  202)=-EM0089                                                          
      A(  203)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  204)=-EM0133                                                          
      A(  205)=-EM0134                                                          
      A(  206)=-EM0135                                                          
      B(    4)=+EM0128                                                          
      SL(    4)=-EM0083                                                         
      A(  207)=+EM0087                                                          
      A(  208)=+EM0090                                                          
      A(  209)=+EM0093                                                          
      EM0137=                                   -EM0037                         
      A(  210)=+EM0136                                                          
      A(  211)=+EM0137                                                          
      A(  212)=-EM0087                                                          
      A(  213)=-EM0090                                                          
      A(  214)=-EM0093                                                          
      EM0139=              +EM0102*EM0068-EM0099*EM0069                         
      EM0140=              +EM0096*EM0069-EM0102*EM0067                         
      EM0141=              +EM0099*EM0067-EM0096*EM0068                         
      A(  215)=-EM0139                                                          
      A(  216)=-EM0140                                                          
      A(  217)=-EM0141                                                          
      B(    5)=+EM0129                                                          
      SL(    5)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0052                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  487))                                             
      EQUIVALENCE(EM0011,GR(  488))                                             
      EQUIVALENCE(EM0012,GR(  489))                                             
      EQUIVALENCE(EM0013,GR(  490))                                             
      EQUIVALENCE(EM0014,GR(  491))                                             
      EQUIVALENCE(EM0015,GR(  492))                                             
      EQUIVALENCE(EM0016,GR(  493))                                             
      EQUIVALENCE(EM0017,GR(  494))                                             
      EQUIVALENCE(EM0018,GR(  495))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  286))                                             
      EQUIVALENCE(EM0025,GR(  287))                                             
      EQUIVALENCE(EM0020,GR(  288))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(  121))                                             
      EQUIVALENCE(EM0029,GR(  122))                                             
      EQUIVALENCE(EM0030,GR(  123))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  283))                                             
      EQUIVALENCE(EM0032,GR(  284))                                             
      EQUIVALENCE(EM0033,GR(  285))                                             
      EQUIVALENCE(EM0034,GR(  286))                                             
      EQUIVALENCE(EM0035,GR(  287))                                             
      EQUIVALENCE(EM0036,GR(  288))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  410))                                             
      EQUIVALENCE(EM0038,GV(  405))                                             
      EQUIVALENCE(EM0039,GV(  404))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  541))                                             
      EQUIVALENCE(EM0041,GR(  542))                                             
      EQUIVALENCE(EM0042,GR(  543))                                             
      EQUIVALENCE(EM0043,GR(  544))                                             
      EQUIVALENCE(EM0044,GR(  545))                                             
      EQUIVALENCE(EM0045,GR(  546))                                             
      EQUIVALENCE(EM0046,GR(  547))                                             
      EQUIVALENCE(EM0047,GR(  548))                                             
      EQUIVALENCE(EM0048,GR(  549))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  280))                                             
      EQUIVALENCE(EM0055,GR(  281))                                             
      EQUIVALENCE(EM0050,GR(  282))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(  115))                                             
      EQUIVALENCE(EM0059,GR(  116))                                             
      EQUIVALENCE(EM0060,GR(  117))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  277))                                             
      EQUIVALENCE(EM0062,GR(  278))                                             
      EQUIVALENCE(EM0063,GR(  279))                                             
      EQUIVALENCE(EM0064,GR(  280))                                             
      EQUIVALENCE(EM0065,GR(  281))                                             
      EQUIVALENCE(EM0066,GR(  282))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  396))                                             
      EQUIVALENCE(EM0068,GV(  389))                                             
      EQUIVALENCE(EM0069,GV(  388))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0105,EM0037)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0130,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  218)=+EM0086                                                          
      A(  219)=+EM0089                                                          
      A(  220)=+EM0092                                                          
      EM0103=                                   -EM0039                         
      A(  221)=+EM0103                                                          
      A(  222)=+EM0105                                                          
      A(  223)=-EM0086                                                          
      A(  224)=-EM0089                                                          
      A(  225)=-EM0092                                                          
      EM0106=              +EM0101*EM0068-EM0098*EM0069                         
      EM0107=              +EM0095*EM0069-EM0101*EM0067                         
      EM0108=              +EM0098*EM0067-EM0095*EM0068                         
      A(  226)=-EM0106                                                          
      A(  227)=-EM0107                                                          
      A(  228)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(    6)=+EM0128                                                          
      SL(    6)=-EM0083                                                         
      A(  229)=+EM0087                                                          
      A(  230)=+EM0090                                                          
      A(  231)=+EM0093                                                          
      EM0131=                                   -EM0037                         
      A(  232)=+EM0130                                                          
      A(  233)=+EM0131                                                          
      A(  234)=-EM0087                                                          
      A(  235)=-EM0090                                                          
      A(  236)=-EM0093                                                          
      EM0133=              +EM0102*EM0068-EM0099*EM0069                         
      EM0134=              +EM0096*EM0069-EM0102*EM0067                         
      EM0135=              +EM0099*EM0067-EM0096*EM0068                         
      A(  237)=-EM0133                                                          
      A(  238)=-EM0134                                                          
      A(  239)=-EM0135                                                          
      B(    7)=+EM0129                                                          
      SL(    7)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0051                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  487))                                             
      EQUIVALENCE(EM0011,GR(  488))                                             
      EQUIVALENCE(EM0012,GR(  489))                                             
      EQUIVALENCE(EM0013,GR(  490))                                             
      EQUIVALENCE(EM0014,GR(  491))                                             
      EQUIVALENCE(EM0015,GR(  492))                                             
      EQUIVALENCE(EM0016,GR(  493))                                             
      EQUIVALENCE(EM0017,GR(  494))                                             
      EQUIVALENCE(EM0018,GR(  495))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  286))                                             
      EQUIVALENCE(EM0025,GR(  287))                                             
      EQUIVALENCE(EM0020,GR(  288))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(  121))                                             
      EQUIVALENCE(EM0029,GR(  122))                                             
      EQUIVALENCE(EM0030,GR(  123))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  283))                                             
      EQUIVALENCE(EM0032,GR(  284))                                             
      EQUIVALENCE(EM0033,GR(  285))                                             
      EQUIVALENCE(EM0034,GR(  286))                                             
      EQUIVALENCE(EM0035,GR(  287))                                             
      EQUIVALENCE(EM0036,GR(  288))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  411))                                             
      EQUIVALENCE(EM0038,GV(  407))                                             
      EQUIVALENCE(EM0039,GV(  406))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  541))                                             
      EQUIVALENCE(EM0041,GR(  542))                                             
      EQUIVALENCE(EM0042,GR(  543))                                             
      EQUIVALENCE(EM0043,GR(  544))                                             
      EQUIVALENCE(EM0044,GR(  545))                                             
      EQUIVALENCE(EM0045,GR(  546))                                             
      EQUIVALENCE(EM0046,GR(  547))                                             
      EQUIVALENCE(EM0047,GR(  548))                                             
      EQUIVALENCE(EM0048,GR(  549))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  280))                                             
      EQUIVALENCE(EM0055,GR(  281))                                             
      EQUIVALENCE(EM0050,GR(  282))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(  115))                                             
      EQUIVALENCE(EM0059,GR(  116))                                             
      EQUIVALENCE(EM0060,GR(  117))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  277))                                             
      EQUIVALENCE(EM0062,GR(  278))                                             
      EQUIVALENCE(EM0063,GR(  279))                                             
      EQUIVALENCE(EM0064,GR(  280))                                             
      EQUIVALENCE(EM0065,GR(  281))                                             
      EQUIVALENCE(EM0066,GR(  282))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  397))                                             
      EQUIVALENCE(EM0068,GV(  391))                                             
      EQUIVALENCE(EM0069,GV(  390))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
      EQUIVALENCE(EM0136,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  240)=+EM0085                                                          
      A(  241)=+EM0088                                                          
      A(  242)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  243)=+EM0104                                                          
      A(  244)=+EM0105                                                          
      A(  245)=-EM0085                                                          
      A(  246)=-EM0088                                                          
      A(  247)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  248)=-EM0106                                                          
      A(  249)=-EM0107                                                          
      A(  250)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(    8)=+EM0127                                                          
      SL(    8)=-EM0082                                                         
      A(  251)=+EM0086                                                          
      A(  252)=+EM0089                                                          
      A(  253)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  254)=+EM0130                                                          
      A(  255)=+EM0132                                                          
      A(  256)=-EM0086                                                          
      A(  257)=-EM0089                                                          
      A(  258)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  259)=-EM0133                                                          
      A(  260)=-EM0134                                                          
      A(  261)=-EM0135                                                          
      B(    9)=+EM0128                                                          
      SL(    9)=-EM0083                                                         
      A(  262)=+EM0087                                                          
      A(  263)=+EM0090                                                          
      A(  264)=+EM0093                                                          
      EM0137=                                   -EM0037                         
      A(  265)=+EM0136                                                          
      A(  266)=+EM0137                                                          
      A(  267)=-EM0087                                                          
      A(  268)=-EM0090                                                          
      A(  269)=-EM0093                                                          
      EM0139=              +EM0102*EM0068-EM0099*EM0069                         
      EM0140=              +EM0096*EM0069-EM0102*EM0067                         
      EM0141=              +EM0099*EM0067-EM0096*EM0068                         
      A(  270)=-EM0139                                                          
      A(  271)=-EM0140                                                          
      A(  272)=-EM0141                                                          
      B(   10)=+EM0129                                                          
      SL(   10)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0050                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  578))                                             
      EQUIVALENCE(EM0011,GR(  579))                                             
      EQUIVALENCE(EM0012,GR(  580))                                             
      EQUIVALENCE(EM0013,GR(  581))                                             
      EQUIVALENCE(EM0014,GR(  582))                                             
      EQUIVALENCE(EM0015,GR(  583))                                             
      EQUIVALENCE(EM0016,GR(  584))                                             
      EQUIVALENCE(EM0017,GR(  585))                                             
      EQUIVALENCE(EM0018,GR(  586))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  274))                                             
      EQUIVALENCE(EM0025,GR(  275))                                             
      EQUIVALENCE(EM0020,GR(  276))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(  109))                                             
      EQUIVALENCE(EM0029,GR(  110))                                             
      EQUIVALENCE(EM0030,GR(  111))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  271))                                             
      EQUIVALENCE(EM0032,GR(  272))                                             
      EQUIVALENCE(EM0033,GR(  273))                                             
      EQUIVALENCE(EM0034,GR(  274))                                             
      EQUIVALENCE(EM0035,GR(  275))                                             
      EQUIVALENCE(EM0036,GR(  276))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  384))                                             
      EQUIVALENCE(EM0038,GV(  377))                                             
      EQUIVALENCE(EM0039,GV(  376))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  541))                                             
      EQUIVALENCE(EM0041,GR(  542))                                             
      EQUIVALENCE(EM0042,GR(  543))                                             
      EQUIVALENCE(EM0043,GR(  544))                                             
      EQUIVALENCE(EM0044,GR(  545))                                             
      EQUIVALENCE(EM0045,GR(  546))                                             
      EQUIVALENCE(EM0046,GR(  547))                                             
      EQUIVALENCE(EM0047,GR(  548))                                             
      EQUIVALENCE(EM0048,GR(  549))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  280))                                             
      EQUIVALENCE(EM0055,GR(  281))                                             
      EQUIVALENCE(EM0050,GR(  282))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(  115))                                             
      EQUIVALENCE(EM0059,GR(  116))                                             
      EQUIVALENCE(EM0060,GR(  117))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  277))                                             
      EQUIVALENCE(EM0062,GR(  278))                                             
      EQUIVALENCE(EM0063,GR(  279))                                             
      EQUIVALENCE(EM0064,GR(  280))                                             
      EQUIVALENCE(EM0065,GR(  281))                                             
      EQUIVALENCE(EM0066,GR(  282))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  398))                                             
      EQUIVALENCE(EM0068,GV(  393))                                             
      EQUIVALENCE(EM0069,GV(  392))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  273)=+EM0085                                                          
      A(  274)=+EM0088                                                          
      A(  275)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  276)=+EM0104                                                          
      A(  277)=+EM0105                                                          
      A(  278)=-EM0085                                                          
      A(  279)=-EM0088                                                          
      A(  280)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  281)=-EM0106                                                          
      A(  282)=-EM0107                                                          
      A(  283)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   11)=+EM0127                                                          
      SL(   11)=-EM0082                                                         
      A(  284)=+EM0086                                                          
      A(  285)=+EM0089                                                          
      A(  286)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  287)=+EM0130                                                          
      A(  288)=+EM0132                                                          
      A(  289)=-EM0086                                                          
      A(  290)=-EM0089                                                          
      A(  291)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  292)=-EM0133                                                          
      A(  293)=-EM0134                                                          
      A(  294)=-EM0135                                                          
      B(   12)=+EM0128                                                          
      SL(   12)=-EM0083                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0049                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  541))                                             
      EQUIVALENCE(EM0011,GR(  542))                                             
      EQUIVALENCE(EM0012,GR(  543))                                             
      EQUIVALENCE(EM0013,GR(  544))                                             
      EQUIVALENCE(EM0014,GR(  545))                                             
      EQUIVALENCE(EM0015,GR(  546))                                             
      EQUIVALENCE(EM0016,GR(  547))                                             
      EQUIVALENCE(EM0017,GR(  548))                                             
      EQUIVALENCE(EM0018,GR(  549))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  280))                                             
      EQUIVALENCE(EM0025,GR(  281))                                             
      EQUIVALENCE(EM0020,GR(  282))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(  115))                                             
      EQUIVALENCE(EM0029,GR(  116))                                             
      EQUIVALENCE(EM0030,GR(  117))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  277))                                             
      EQUIVALENCE(EM0032,GR(  278))                                             
      EQUIVALENCE(EM0033,GR(  279))                                             
      EQUIVALENCE(EM0034,GR(  280))                                             
      EQUIVALENCE(EM0035,GR(  281))                                             
      EQUIVALENCE(EM0036,GR(  282))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  399))                                             
      EQUIVALENCE(EM0038,GV(  395))                                             
      EQUIVALENCE(EM0039,GV(  394))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  578))                                             
      EQUIVALENCE(EM0041,GR(  579))                                             
      EQUIVALENCE(EM0042,GR(  580))                                             
      EQUIVALENCE(EM0043,GR(  581))                                             
      EQUIVALENCE(EM0044,GR(  582))                                             
      EQUIVALENCE(EM0045,GR(  583))                                             
      EQUIVALENCE(EM0046,GR(  584))                                             
      EQUIVALENCE(EM0047,GR(  585))                                             
      EQUIVALENCE(EM0048,GR(  586))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  274))                                             
      EQUIVALENCE(EM0055,GR(  275))                                             
      EQUIVALENCE(EM0050,GR(  276))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(  109))                                             
      EQUIVALENCE(EM0059,GR(  110))                                             
      EQUIVALENCE(EM0060,GR(  111))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  271))                                             
      EQUIVALENCE(EM0062,GR(  272))                                             
      EQUIVALENCE(EM0063,GR(  273))                                             
      EQUIVALENCE(EM0064,GR(  274))                                             
      EQUIVALENCE(EM0065,GR(  275))                                             
      EQUIVALENCE(EM0066,GR(  276))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  385))                                             
      EQUIVALENCE(EM0068,GV(  379))                                             
      EQUIVALENCE(EM0069,GV(  378))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
      EQUIVALENCE(EM0136,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  295)=+EM0085                                                          
      A(  296)=+EM0088                                                          
      A(  297)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  298)=+EM0104                                                          
      A(  299)=+EM0105                                                          
      A(  300)=-EM0085                                                          
      A(  301)=-EM0088                                                          
      A(  302)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  303)=-EM0106                                                          
      A(  304)=-EM0107                                                          
      A(  305)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   13)=+EM0127                                                          
      SL(   13)=-EM0082                                                         
      A(  306)=+EM0086                                                          
      A(  307)=+EM0089                                                          
      A(  308)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  309)=+EM0130                                                          
      A(  310)=+EM0132                                                          
      A(  311)=-EM0086                                                          
      A(  312)=-EM0089                                                          
      A(  313)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  314)=-EM0133                                                          
      A(  315)=-EM0134                                                          
      A(  316)=-EM0135                                                          
      B(   14)=+EM0128                                                          
      SL(   14)=-EM0083                                                         
      A(  317)=+EM0087                                                          
      A(  318)=+EM0090                                                          
      A(  319)=+EM0093                                                          
      EM0137=                                   -EM0037                         
      A(  320)=+EM0136                                                          
      A(  321)=+EM0137                                                          
      A(  322)=-EM0087                                                          
      A(  323)=-EM0090                                                          
      A(  324)=-EM0093                                                          
      EM0139=              +EM0102*EM0068-EM0099*EM0069                         
      EM0140=              +EM0096*EM0069-EM0102*EM0067                         
      EM0141=              +EM0099*EM0067-EM0096*EM0068                         
      A(  325)=-EM0139                                                          
      A(  326)=-EM0140                                                          
      A(  327)=-EM0141                                                          
      B(   15)=+EM0129                                                          
      SL(   15)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0040                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  615))                                             
      EQUIVALENCE(EM0011,GR(  616))                                             
      EQUIVALENCE(EM0012,GR(  617))                                             
      EQUIVALENCE(EM0013,GR(  618))                                             
      EQUIVALENCE(EM0014,GR(  619))                                             
      EQUIVALENCE(EM0015,GR(  620))                                             
      EQUIVALENCE(EM0016,GR(  621))                                             
      EQUIVALENCE(EM0017,GR(  622))                                             
      EQUIVALENCE(EM0018,GR(  623))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  262))                                             
      EQUIVALENCE(EM0025,GR(  263))                                             
      EQUIVALENCE(EM0020,GR(  264))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   97))                                             
      EQUIVALENCE(EM0029,GR(   98))                                             
      EQUIVALENCE(EM0030,GR(   99))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  259))                                             
      EQUIVALENCE(EM0032,GR(  260))                                             
      EQUIVALENCE(EM0033,GR(  261))                                             
      EQUIVALENCE(EM0034,GR(  262))                                             
      EQUIVALENCE(EM0035,GR(  263))                                             
      EQUIVALENCE(EM0036,GR(  264))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  366))                                             
      EQUIVALENCE(EM0038,GV(  359))                                             
      EQUIVALENCE(EM0039,GV(  358))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  632))                                             
      EQUIVALENCE(EM0041,GR(  633))                                             
      EQUIVALENCE(EM0042,GR(  634))                                             
      EQUIVALENCE(EM0043,GR(  635))                                             
      EQUIVALENCE(EM0044,GR(  636))                                             
      EQUIVALENCE(EM0045,GR(  637))                                             
      EQUIVALENCE(EM0046,GR(  638))                                             
      EQUIVALENCE(EM0047,GR(  639))                                             
      EQUIVALENCE(EM0048,GR(  640))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  268))                                             
      EQUIVALENCE(EM0055,GR(  269))                                             
      EQUIVALENCE(EM0050,GR(  270))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(  103))                                             
      EQUIVALENCE(EM0059,GR(  104))                                             
      EQUIVALENCE(EM0060,GR(  105))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  265))                                             
      EQUIVALENCE(EM0062,GR(  266))                                             
      EQUIVALENCE(EM0063,GR(  267))                                             
      EQUIVALENCE(EM0064,GR(  268))                                             
      EQUIVALENCE(EM0065,GR(  269))                                             
      EQUIVALENCE(EM0066,GR(  270))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  374))                                             
      EQUIVALENCE(EM0068,GV(  371))                                             
      EQUIVALENCE(EM0069,GV(  370))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0105,EM0037)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0130,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  328)=+EM0086                                                          
      A(  329)=+EM0089                                                          
      A(  330)=+EM0092                                                          
      EM0103=                                   -EM0039                         
      A(  331)=+EM0103                                                          
      A(  332)=+EM0105                                                          
      A(  333)=-EM0086                                                          
      A(  334)=-EM0089                                                          
      A(  335)=-EM0092                                                          
      EM0106=              +EM0101*EM0068-EM0098*EM0069                         
      EM0107=              +EM0095*EM0069-EM0101*EM0067                         
      EM0108=              +EM0098*EM0067-EM0095*EM0068                         
      A(  336)=-EM0106                                                          
      A(  337)=-EM0107                                                          
      A(  338)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   16)=+EM0128                                                          
      SL(   16)=-EM0083                                                         
      A(  339)=+EM0087                                                          
      A(  340)=+EM0090                                                          
      A(  341)=+EM0093                                                          
      EM0131=                                   -EM0037                         
      A(  342)=+EM0130                                                          
      A(  343)=+EM0131                                                          
      A(  344)=-EM0087                                                          
      A(  345)=-EM0090                                                          
      A(  346)=-EM0093                                                          
      EM0133=              +EM0102*EM0068-EM0099*EM0069                         
      EM0134=              +EM0096*EM0069-EM0102*EM0067                         
      EM0135=              +EM0099*EM0067-EM0096*EM0068                         
      A(  347)=-EM0133                                                          
      A(  348)=-EM0134                                                          
      A(  349)=-EM0135                                                          
      B(   17)=+EM0129                                                          
      SL(   17)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0039                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  615))                                             
      EQUIVALENCE(EM0011,GR(  616))                                             
      EQUIVALENCE(EM0012,GR(  617))                                             
      EQUIVALENCE(EM0013,GR(  618))                                             
      EQUIVALENCE(EM0014,GR(  619))                                             
      EQUIVALENCE(EM0015,GR(  620))                                             
      EQUIVALENCE(EM0016,GR(  621))                                             
      EQUIVALENCE(EM0017,GR(  622))                                             
      EQUIVALENCE(EM0018,GR(  623))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  262))                                             
      EQUIVALENCE(EM0025,GR(  263))                                             
      EQUIVALENCE(EM0020,GR(  264))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   97))                                             
      EQUIVALENCE(EM0029,GR(   98))                                             
      EQUIVALENCE(EM0030,GR(   99))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  259))                                             
      EQUIVALENCE(EM0032,GR(  260))                                             
      EQUIVALENCE(EM0033,GR(  261))                                             
      EQUIVALENCE(EM0034,GR(  262))                                             
      EQUIVALENCE(EM0035,GR(  263))                                             
      EQUIVALENCE(EM0036,GR(  264))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  367))                                             
      EQUIVALENCE(EM0038,GV(  361))                                             
      EQUIVALENCE(EM0039,GV(  360))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  632))                                             
      EQUIVALENCE(EM0041,GR(  633))                                             
      EQUIVALENCE(EM0042,GR(  634))                                             
      EQUIVALENCE(EM0043,GR(  635))                                             
      EQUIVALENCE(EM0044,GR(  636))                                             
      EQUIVALENCE(EM0045,GR(  637))                                             
      EQUIVALENCE(EM0046,GR(  638))                                             
      EQUIVALENCE(EM0047,GR(  639))                                             
      EQUIVALENCE(EM0048,GR(  640))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  268))                                             
      EQUIVALENCE(EM0055,GR(  269))                                             
      EQUIVALENCE(EM0050,GR(  270))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(  103))                                             
      EQUIVALENCE(EM0059,GR(  104))                                             
      EQUIVALENCE(EM0060,GR(  105))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  265))                                             
      EQUIVALENCE(EM0062,GR(  266))                                             
      EQUIVALENCE(EM0063,GR(  267))                                             
      EQUIVALENCE(EM0064,GR(  268))                                             
      EQUIVALENCE(EM0065,GR(  269))                                             
      EQUIVALENCE(EM0066,GR(  270))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  375))                                             
      EQUIVALENCE(EM0068,GV(  373))                                             
      EQUIVALENCE(EM0069,GV(  372))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
      EQUIVALENCE(EM0136,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  350)=+EM0085                                                          
      A(  351)=+EM0088                                                          
      A(  352)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  353)=+EM0104                                                          
      A(  354)=+EM0105                                                          
      A(  355)=-EM0085                                                          
      A(  356)=-EM0088                                                          
      A(  357)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  358)=-EM0106                                                          
      A(  359)=-EM0107                                                          
      A(  360)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   18)=+EM0127                                                          
      SL(   18)=-EM0082                                                         
      A(  361)=+EM0086                                                          
      A(  362)=+EM0089                                                          
      A(  363)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  364)=+EM0130                                                          
      A(  365)=+EM0132                                                          
      A(  366)=-EM0086                                                          
      A(  367)=-EM0089                                                          
      A(  368)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  369)=-EM0133                                                          
      A(  370)=-EM0134                                                          
      A(  371)=-EM0135                                                          
      B(   19)=+EM0128                                                          
      SL(   19)=-EM0083                                                         
      A(  372)=+EM0087                                                          
      A(  373)=+EM0090                                                          
      A(  374)=+EM0093                                                          
      EM0137=                                   -EM0037                         
      A(  375)=+EM0136                                                          
      A(  376)=+EM0137                                                          
      A(  377)=-EM0087                                                          
      A(  378)=-EM0090                                                          
      A(  379)=-EM0093                                                          
      EM0139=              +EM0102*EM0068-EM0099*EM0069                         
      EM0140=              +EM0096*EM0069-EM0102*EM0067                         
      EM0141=              +EM0099*EM0067-EM0096*EM0068                         
      A(  380)=-EM0139                                                          
      A(  381)=-EM0140                                                          
      A(  382)=-EM0141                                                          
      B(   20)=+EM0129                                                          
      SL(   20)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0096                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  669))                                             
      EQUIVALENCE(EM0011,GR(  670))                                             
      EQUIVALENCE(EM0012,GR(  671))                                             
      EQUIVALENCE(EM0013,GR(  672))                                             
      EQUIVALENCE(EM0014,GR(  673))                                             
      EQUIVALENCE(EM0015,GR(  674))                                             
      EQUIVALENCE(EM0016,GR(  675))                                             
      EQUIVALENCE(EM0017,GR(  676))                                             
      EQUIVALENCE(EM0018,GR(  677))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  256))                                             
      EQUIVALENCE(EM0025,GR(  257))                                             
      EQUIVALENCE(EM0020,GR(  258))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   91))                                             
      EQUIVALENCE(EM0029,GR(   92))                                             
      EQUIVALENCE(EM0030,GR(   93))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  253))                                             
      EQUIVALENCE(EM0032,GR(  254))                                             
      EQUIVALENCE(EM0033,GR(  255))                                             
      EQUIVALENCE(EM0034,GR(  256))                                             
      EQUIVALENCE(EM0035,GR(  257))                                             
      EQUIVALENCE(EM0036,GR(  258))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  354))                                             
      EQUIVALENCE(EM0038,GV(  347))                                             
      EQUIVALENCE(EM0039,GV(  346))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  686))                                             
      EQUIVALENCE(EM0041,GR(  687))                                             
      EQUIVALENCE(EM0042,GR(  688))                                             
      EQUIVALENCE(EM0043,GR(  689))                                             
      EQUIVALENCE(EM0044,GR(  690))                                             
      EQUIVALENCE(EM0045,GR(  691))                                             
      EQUIVALENCE(EM0046,GR(  692))                                             
      EQUIVALENCE(EM0047,GR(  693))                                             
      EQUIVALENCE(EM0048,GR(  694))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  310))                                             
      EQUIVALENCE(EM0055,GR(  311))                                             
      EQUIVALENCE(EM0050,GR(  312))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(  145))                                             
      EQUIVALENCE(EM0059,GR(  146))                                             
      EQUIVALENCE(EM0060,GR(  147))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  307))                                             
      EQUIVALENCE(EM0062,GR(  308))                                             
      EQUIVALENCE(EM0063,GR(  309))                                             
      EQUIVALENCE(EM0064,GR(  310))                                             
      EQUIVALENCE(EM0065,GR(  311))                                             
      EQUIVALENCE(EM0066,GR(  312))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  442))                                             
      EQUIVALENCE(EM0068,GV(  443))                                             
      EQUIVALENCE(EM0069,GV(  444))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  383)=+EM0085                                                          
      A(  384)=+EM0088                                                          
      A(  385)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  386)=+EM0104                                                          
      A(  387)=+EM0105                                                          
      A(  388)=-EM0085                                                          
      A(  389)=-EM0088                                                          
      A(  390)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  391)=-EM0106                                                          
      A(  392)=-EM0107                                                          
      A(  393)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   21)=+EM0127                                                          
      SL(   21)=-EM0082                                                         
      A(  394)=+EM0086                                                          
      A(  395)=+EM0089                                                          
      A(  396)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  397)=+EM0130                                                          
      A(  398)=+EM0132                                                          
      A(  399)=-EM0086                                                          
      A(  400)=-EM0089                                                          
      A(  401)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  402)=-EM0133                                                          
      A(  403)=-EM0134                                                          
      A(  404)=-EM0135                                                          
      B(   22)=+EM0128                                                          
      SL(   22)=-EM0083                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0036                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  711))                                             
      EQUIVALENCE(EM0011,GR(  712))                                             
      EQUIVALENCE(EM0012,GR(  713))                                             
      EQUIVALENCE(EM0013,GR(  714))                                             
      EQUIVALENCE(EM0014,GR(  715))                                             
      EQUIVALENCE(EM0015,GR(  716))                                             
      EQUIVALENCE(EM0016,GR(  717))                                             
      EQUIVALENCE(EM0017,GR(  718))                                             
      EQUIVALENCE(EM0018,GR(  719))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  250))                                             
      EQUIVALENCE(EM0025,GR(  251))                                             
      EQUIVALENCE(EM0020,GR(  252))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   85))                                             
      EQUIVALENCE(EM0029,GR(   86))                                             
      EQUIVALENCE(EM0030,GR(   87))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  247))                                             
      EQUIVALENCE(EM0032,GR(  248))                                             
      EQUIVALENCE(EM0033,GR(  249))                                             
      EQUIVALENCE(EM0034,GR(  250))                                             
      EQUIVALENCE(EM0035,GR(  251))                                             
      EQUIVALENCE(EM0036,GR(  252))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  342))                                             
      EQUIVALENCE(EM0038,GV(  335))                                             
      EQUIVALENCE(EM0039,GV(  334))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  669))                                             
      EQUIVALENCE(EM0041,GR(  670))                                             
      EQUIVALENCE(EM0042,GR(  671))                                             
      EQUIVALENCE(EM0043,GR(  672))                                             
      EQUIVALENCE(EM0044,GR(  673))                                             
      EQUIVALENCE(EM0045,GR(  674))                                             
      EQUIVALENCE(EM0046,GR(  675))                                             
      EQUIVALENCE(EM0047,GR(  676))                                             
      EQUIVALENCE(EM0048,GR(  677))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  256))                                             
      EQUIVALENCE(EM0055,GR(  257))                                             
      EQUIVALENCE(EM0050,GR(  258))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   91))                                             
      EQUIVALENCE(EM0059,GR(   92))                                             
      EQUIVALENCE(EM0060,GR(   93))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  253))                                             
      EQUIVALENCE(EM0062,GR(  254))                                             
      EQUIVALENCE(EM0063,GR(  255))                                             
      EQUIVALENCE(EM0064,GR(  256))                                             
      EQUIVALENCE(EM0065,GR(  257))                                             
      EQUIVALENCE(EM0066,GR(  258))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  355))                                             
      EQUIVALENCE(EM0068,GV(  349))                                             
      EQUIVALENCE(EM0069,GV(  348))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0105,EM0037)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0130,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  405)=+EM0086                                                          
      A(  406)=+EM0089                                                          
      A(  407)=+EM0092                                                          
      EM0103=                                   -EM0039                         
      A(  408)=+EM0103                                                          
      A(  409)=+EM0105                                                          
      A(  410)=-EM0086                                                          
      A(  411)=-EM0089                                                          
      A(  412)=-EM0092                                                          
      EM0106=              +EM0101*EM0068-EM0098*EM0069                         
      EM0107=              +EM0095*EM0069-EM0101*EM0067                         
      EM0108=              +EM0098*EM0067-EM0095*EM0068                         
      A(  413)=-EM0106                                                          
      A(  414)=-EM0107                                                          
      A(  415)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   23)=+EM0128                                                          
      SL(   23)=-EM0083                                                         
      A(  416)=+EM0087                                                          
      A(  417)=+EM0090                                                          
      A(  418)=+EM0093                                                          
      EM0131=                                   -EM0037                         
      A(  419)=+EM0130                                                          
      A(  420)=+EM0131                                                          
      A(  421)=-EM0087                                                          
      A(  422)=-EM0090                                                          
      A(  423)=-EM0093                                                          
      EM0133=              +EM0102*EM0068-EM0099*EM0069                         
      EM0134=              +EM0096*EM0069-EM0102*EM0067                         
      EM0135=              +EM0099*EM0067-EM0096*EM0068                         
      A(  424)=-EM0133                                                          
      A(  425)=-EM0134                                                          
      A(  426)=-EM0135                                                          
      B(   24)=+EM0129                                                          
      SL(   24)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0035                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  711))                                             
      EQUIVALENCE(EM0011,GR(  712))                                             
      EQUIVALENCE(EM0012,GR(  713))                                             
      EQUIVALENCE(EM0013,GR(  714))                                             
      EQUIVALENCE(EM0014,GR(  715))                                             
      EQUIVALENCE(EM0015,GR(  716))                                             
      EQUIVALENCE(EM0016,GR(  717))                                             
      EQUIVALENCE(EM0017,GR(  718))                                             
      EQUIVALENCE(EM0018,GR(  719))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  250))                                             
      EQUIVALENCE(EM0025,GR(  251))                                             
      EQUIVALENCE(EM0020,GR(  252))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   85))                                             
      EQUIVALENCE(EM0029,GR(   86))                                             
      EQUIVALENCE(EM0030,GR(   87))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  247))                                             
      EQUIVALENCE(EM0032,GR(  248))                                             
      EQUIVALENCE(EM0033,GR(  249))                                             
      EQUIVALENCE(EM0034,GR(  250))                                             
      EQUIVALENCE(EM0035,GR(  251))                                             
      EQUIVALENCE(EM0036,GR(  252))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  343))                                             
      EQUIVALENCE(EM0038,GV(  337))                                             
      EQUIVALENCE(EM0039,GV(  336))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  669))                                             
      EQUIVALENCE(EM0041,GR(  670))                                             
      EQUIVALENCE(EM0042,GR(  671))                                             
      EQUIVALENCE(EM0043,GR(  672))                                             
      EQUIVALENCE(EM0044,GR(  673))                                             
      EQUIVALENCE(EM0045,GR(  674))                                             
      EQUIVALENCE(EM0046,GR(  675))                                             
      EQUIVALENCE(EM0047,GR(  676))                                             
      EQUIVALENCE(EM0048,GR(  677))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  256))                                             
      EQUIVALENCE(EM0055,GR(  257))                                             
      EQUIVALENCE(EM0050,GR(  258))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   91))                                             
      EQUIVALENCE(EM0059,GR(   92))                                             
      EQUIVALENCE(EM0060,GR(   93))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  253))                                             
      EQUIVALENCE(EM0062,GR(  254))                                             
      EQUIVALENCE(EM0063,GR(  255))                                             
      EQUIVALENCE(EM0064,GR(  256))                                             
      EQUIVALENCE(EM0065,GR(  257))                                             
      EQUIVALENCE(EM0066,GR(  258))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  356))                                             
      EQUIVALENCE(EM0068,GV(  351))                                             
      EQUIVALENCE(EM0069,GV(  350))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
      EQUIVALENCE(EM0136,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  427)=+EM0085                                                          
      A(  428)=+EM0088                                                          
      A(  429)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  430)=+EM0104                                                          
      A(  431)=+EM0105                                                          
      A(  432)=-EM0085                                                          
      A(  433)=-EM0088                                                          
      A(  434)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  435)=-EM0106                                                          
      A(  436)=-EM0107                                                          
      A(  437)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   25)=+EM0127                                                          
      SL(   25)=-EM0082                                                         
      A(  438)=+EM0086                                                          
      A(  439)=+EM0089                                                          
      A(  440)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  441)=+EM0130                                                          
      A(  442)=+EM0132                                                          
      A(  443)=-EM0086                                                          
      A(  444)=-EM0089                                                          
      A(  445)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  446)=-EM0133                                                          
      A(  447)=-EM0134                                                          
      A(  448)=-EM0135                                                          
      B(   26)=+EM0128                                                          
      SL(   26)=-EM0083                                                         
      A(  449)=+EM0087                                                          
      A(  450)=+EM0090                                                          
      A(  451)=+EM0093                                                          
      EM0137=                                   -EM0037                         
      A(  452)=+EM0136                                                          
      A(  453)=+EM0137                                                          
      A(  454)=-EM0087                                                          
      A(  455)=-EM0090                                                          
      A(  456)=-EM0093                                                          
      EM0139=              +EM0102*EM0068-EM0099*EM0069                         
      EM0140=              +EM0096*EM0069-EM0102*EM0067                         
      EM0141=              +EM0099*EM0067-EM0096*EM0068                         
      A(  457)=-EM0139                                                          
      A(  458)=-EM0140                                                          
      A(  459)=-EM0141                                                          
      B(   27)=+EM0129                                                          
      SL(   27)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0086                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  669))                                             
      EQUIVALENCE(EM0011,GR(  670))                                             
      EQUIVALENCE(EM0012,GR(  671))                                             
      EQUIVALENCE(EM0013,GR(  672))                                             
      EQUIVALENCE(EM0014,GR(  673))                                             
      EQUIVALENCE(EM0015,GR(  674))                                             
      EQUIVALENCE(EM0016,GR(  675))                                             
      EQUIVALENCE(EM0017,GR(  676))                                             
      EQUIVALENCE(EM0018,GR(  677))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  256))                                             
      EQUIVALENCE(EM0025,GR(  257))                                             
      EQUIVALENCE(EM0020,GR(  258))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   91))                                             
      EQUIVALENCE(EM0029,GR(   92))                                             
      EQUIVALENCE(EM0030,GR(   93))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  253))                                             
      EQUIVALENCE(EM0032,GR(  254))                                             
      EQUIVALENCE(EM0033,GR(  255))                                             
      EQUIVALENCE(EM0034,GR(  256))                                             
      EQUIVALENCE(EM0035,GR(  257))                                             
      EQUIVALENCE(EM0036,GR(  258))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  357))                                             
      EQUIVALENCE(EM0038,GV(  353))                                             
      EQUIVALENCE(EM0039,GV(  352))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  748))                                             
      EQUIVALENCE(EM0041,GR(  749))                                             
      EQUIVALENCE(EM0042,GR(  750))                                             
      EQUIVALENCE(EM0043,GR(  751))                                             
      EQUIVALENCE(EM0044,GR(  752))                                             
      EQUIVALENCE(EM0045,GR(  753))                                             
      EQUIVALENCE(EM0046,GR(  754))                                             
      EQUIVALENCE(EM0047,GR(  755))                                             
      EQUIVALENCE(EM0048,GR(  756))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  244))                                             
      EQUIVALENCE(EM0055,GR(  245))                                             
      EQUIVALENCE(EM0050,GR(  246))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   79))                                             
      EQUIVALENCE(EM0059,GR(   80))                                             
      EQUIVALENCE(EM0060,GR(   81))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  241))                                             
      EQUIVALENCE(EM0062,GR(  242))                                             
      EQUIVALENCE(EM0063,GR(  243))                                             
      EQUIVALENCE(EM0064,GR(  244))                                             
      EQUIVALENCE(EM0065,GR(  245))                                             
      EQUIVALENCE(EM0066,GR(  246))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  328))                                             
      EQUIVALENCE(EM0068,GV(  317))                                             
      EQUIVALENCE(EM0069,GV(  316))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  460)=+EM0085                                                          
      A(  461)=+EM0088                                                          
      A(  462)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  463)=+EM0104                                                          
      A(  464)=+EM0105                                                          
      A(  465)=-EM0085                                                          
      A(  466)=-EM0088                                                          
      A(  467)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  468)=-EM0106                                                          
      A(  469)=-EM0107                                                          
      A(  470)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   28)=+EM0127                                                          
      SL(   28)=-EM0082                                                         
      A(  471)=+EM0086                                                          
      A(  472)=+EM0089                                                          
      A(  473)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  474)=+EM0130                                                          
      A(  475)=+EM0132                                                          
      A(  476)=-EM0086                                                          
      A(  477)=-EM0089                                                          
      A(  478)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  479)=-EM0133                                                          
      A(  480)=-EM0134                                                          
      A(  481)=-EM0135                                                          
      B(   29)=+EM0128                                                          
      SL(   29)=-EM0083                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0034                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  748))                                             
      EQUIVALENCE(EM0011,GR(  749))                                             
      EQUIVALENCE(EM0012,GR(  750))                                             
      EQUIVALENCE(EM0013,GR(  751))                                             
      EQUIVALENCE(EM0014,GR(  752))                                             
      EQUIVALENCE(EM0015,GR(  753))                                             
      EQUIVALENCE(EM0016,GR(  754))                                             
      EQUIVALENCE(EM0017,GR(  755))                                             
      EQUIVALENCE(EM0018,GR(  756))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  244))                                             
      EQUIVALENCE(EM0025,GR(  245))                                             
      EQUIVALENCE(EM0020,GR(  246))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   79))                                             
      EQUIVALENCE(EM0029,GR(   80))                                             
      EQUIVALENCE(EM0030,GR(   81))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  241))                                             
      EQUIVALENCE(EM0032,GR(  242))                                             
      EQUIVALENCE(EM0033,GR(  243))                                             
      EQUIVALENCE(EM0034,GR(  244))                                             
      EQUIVALENCE(EM0035,GR(  245))                                             
      EQUIVALENCE(EM0036,GR(  246))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  329))                                             
      EQUIVALENCE(EM0038,GV(  319))                                             
      EQUIVALENCE(EM0039,GV(  318))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  711))                                             
      EQUIVALENCE(EM0041,GR(  712))                                             
      EQUIVALENCE(EM0042,GR(  713))                                             
      EQUIVALENCE(EM0043,GR(  714))                                             
      EQUIVALENCE(EM0044,GR(  715))                                             
      EQUIVALENCE(EM0045,GR(  716))                                             
      EQUIVALENCE(EM0046,GR(  717))                                             
      EQUIVALENCE(EM0047,GR(  718))                                             
      EQUIVALENCE(EM0048,GR(  719))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  250))                                             
      EQUIVALENCE(EM0055,GR(  251))                                             
      EQUIVALENCE(EM0050,GR(  252))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   85))                                             
      EQUIVALENCE(EM0059,GR(   86))                                             
      EQUIVALENCE(EM0060,GR(   87))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  247))                                             
      EQUIVALENCE(EM0062,GR(  248))                                             
      EQUIVALENCE(EM0063,GR(  249))                                             
      EQUIVALENCE(EM0064,GR(  250))                                             
      EQUIVALENCE(EM0065,GR(  251))                                             
      EQUIVALENCE(EM0066,GR(  252))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  344))                                             
      EQUIVALENCE(EM0068,GV(  339))                                             
      EQUIVALENCE(EM0069,GV(  338))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0130,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  482)=+EM0085                                                          
      A(  483)=+EM0088                                                          
      A(  484)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  485)=+EM0104                                                          
      A(  486)=+EM0105                                                          
      A(  487)=-EM0085                                                          
      A(  488)=-EM0088                                                          
      A(  489)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  490)=-EM0106                                                          
      A(  491)=-EM0107                                                          
      A(  492)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   30)=+EM0127                                                          
      SL(   30)=-EM0082                                                         
      A(  493)=+EM0087                                                          
      A(  494)=+EM0090                                                          
      A(  495)=+EM0093                                                          
      EM0131=                                   -EM0037                         
      A(  496)=+EM0130                                                          
      A(  497)=+EM0131                                                          
      A(  498)=-EM0087                                                          
      A(  499)=-EM0090                                                          
      A(  500)=-EM0093                                                          
      EM0133=              +EM0102*EM0068-EM0099*EM0069                         
      EM0134=              +EM0096*EM0069-EM0102*EM0067                         
      EM0135=              +EM0099*EM0067-EM0096*EM0068                         
      A(  501)=-EM0133                                                          
      A(  502)=-EM0134                                                          
      A(  503)=-EM0135                                                          
      B(   31)=+EM0129                                                          
      SL(   31)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0033                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  711))                                             
      EQUIVALENCE(EM0011,GR(  712))                                             
      EQUIVALENCE(EM0012,GR(  713))                                             
      EQUIVALENCE(EM0013,GR(  714))                                             
      EQUIVALENCE(EM0014,GR(  715))                                             
      EQUIVALENCE(EM0015,GR(  716))                                             
      EQUIVALENCE(EM0016,GR(  717))                                             
      EQUIVALENCE(EM0017,GR(  718))                                             
      EQUIVALENCE(EM0018,GR(  719))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  250))                                             
      EQUIVALENCE(EM0025,GR(  251))                                             
      EQUIVALENCE(EM0020,GR(  252))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   85))                                             
      EQUIVALENCE(EM0029,GR(   86))                                             
      EQUIVALENCE(EM0030,GR(   87))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  247))                                             
      EQUIVALENCE(EM0032,GR(  248))                                             
      EQUIVALENCE(EM0033,GR(  249))                                             
      EQUIVALENCE(EM0034,GR(  250))                                             
      EQUIVALENCE(EM0035,GR(  251))                                             
      EQUIVALENCE(EM0036,GR(  252))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  345))                                             
      EQUIVALENCE(EM0038,GV(  341))                                             
      EQUIVALENCE(EM0039,GV(  340))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  748))                                             
      EQUIVALENCE(EM0041,GR(  749))                                             
      EQUIVALENCE(EM0042,GR(  750))                                             
      EQUIVALENCE(EM0043,GR(  751))                                             
      EQUIVALENCE(EM0044,GR(  752))                                             
      EQUIVALENCE(EM0045,GR(  753))                                             
      EQUIVALENCE(EM0046,GR(  754))                                             
      EQUIVALENCE(EM0047,GR(  755))                                             
      EQUIVALENCE(EM0048,GR(  756))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  244))                                             
      EQUIVALENCE(EM0055,GR(  245))                                             
      EQUIVALENCE(EM0050,GR(  246))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   79))                                             
      EQUIVALENCE(EM0059,GR(   80))                                             
      EQUIVALENCE(EM0060,GR(   81))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  241))                                             
      EQUIVALENCE(EM0062,GR(  242))                                             
      EQUIVALENCE(EM0063,GR(  243))                                             
      EQUIVALENCE(EM0064,GR(  244))                                             
      EQUIVALENCE(EM0065,GR(  245))                                             
      EQUIVALENCE(EM0066,GR(  246))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  330))                                             
      EQUIVALENCE(EM0068,GV(  321))                                             
      EQUIVALENCE(EM0069,GV(  320))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
      EQUIVALENCE(EM0136,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  504)=+EM0085                                                          
      A(  505)=+EM0088                                                          
      A(  506)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  507)=+EM0104                                                          
      A(  508)=+EM0105                                                          
      A(  509)=-EM0085                                                          
      A(  510)=-EM0088                                                          
      A(  511)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  512)=-EM0106                                                          
      A(  513)=-EM0107                                                          
      A(  514)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   32)=+EM0127                                                          
      SL(   32)=-EM0082                                                         
      A(  515)=+EM0086                                                          
      A(  516)=+EM0089                                                          
      A(  517)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  518)=+EM0130                                                          
      A(  519)=+EM0132                                                          
      A(  520)=-EM0086                                                          
      A(  521)=-EM0089                                                          
      A(  522)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  523)=-EM0133                                                          
      A(  524)=-EM0134                                                          
      A(  525)=-EM0135                                                          
      B(   33)=+EM0128                                                          
      SL(   33)=-EM0083                                                         
      A(  526)=+EM0087                                                          
      A(  527)=+EM0090                                                          
      A(  528)=+EM0093                                                          
      EM0137=                                   -EM0037                         
      A(  529)=+EM0136                                                          
      A(  530)=+EM0137                                                          
      A(  531)=-EM0087                                                          
      A(  532)=-EM0090                                                          
      A(  533)=-EM0093                                                          
      EM0139=              +EM0102*EM0068-EM0099*EM0069                         
      EM0140=              +EM0096*EM0069-EM0102*EM0067                         
      EM0141=              +EM0099*EM0067-EM0096*EM0068                         
      A(  534)=-EM0139                                                          
      A(  535)=-EM0140                                                          
      A(  536)=-EM0141                                                          
      B(   34)=+EM0129                                                          
      SL(   34)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0031                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  748))                                             
      EQUIVALENCE(EM0011,GR(  749))                                             
      EQUIVALENCE(EM0012,GR(  750))                                             
      EQUIVALENCE(EM0013,GR(  751))                                             
      EQUIVALENCE(EM0014,GR(  752))                                             
      EQUIVALENCE(EM0015,GR(  753))                                             
      EQUIVALENCE(EM0016,GR(  754))                                             
      EQUIVALENCE(EM0017,GR(  755))                                             
      EQUIVALENCE(EM0018,GR(  756))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  244))                                             
      EQUIVALENCE(EM0025,GR(  245))                                             
      EQUIVALENCE(EM0020,GR(  246))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   79))                                             
      EQUIVALENCE(EM0029,GR(   80))                                             
      EQUIVALENCE(EM0030,GR(   81))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  241))                                             
      EQUIVALENCE(EM0032,GR(  242))                                             
      EQUIVALENCE(EM0033,GR(  243))                                             
      EQUIVALENCE(EM0034,GR(  244))                                             
      EQUIVALENCE(EM0035,GR(  245))                                             
      EQUIVALENCE(EM0036,GR(  246))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  331))                                             
      EQUIVALENCE(EM0038,GV(  323))                                             
      EQUIVALENCE(EM0039,GV(  322))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  793))                                             
      EQUIVALENCE(EM0041,GR(  794))                                             
      EQUIVALENCE(EM0042,GR(  795))                                             
      EQUIVALENCE(EM0043,GR(  796))                                             
      EQUIVALENCE(EM0044,GR(  797))                                             
      EQUIVALENCE(EM0045,GR(  798))                                             
      EQUIVALENCE(EM0046,GR(  799))                                             
      EQUIVALENCE(EM0047,GR(  800))                                             
      EQUIVALENCE(EM0048,GR(  801))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  238))                                             
      EQUIVALENCE(EM0055,GR(  239))                                             
      EQUIVALENCE(EM0050,GR(  240))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   73))                                             
      EQUIVALENCE(EM0059,GR(   74))                                             
      EQUIVALENCE(EM0060,GR(   75))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  235))                                             
      EQUIVALENCE(EM0062,GR(  236))                                             
      EQUIVALENCE(EM0063,GR(  237))                                             
      EQUIVALENCE(EM0064,GR(  238))                                             
      EQUIVALENCE(EM0065,GR(  239))                                             
      EQUIVALENCE(EM0066,GR(  240))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  310))                                             
      EQUIVALENCE(EM0068,GV(  299))                                             
      EQUIVALENCE(EM0069,GV(  298))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
      EQUIVALENCE(EM0136,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  537)=+EM0085                                                          
      A(  538)=+EM0088                                                          
      A(  539)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  540)=+EM0104                                                          
      A(  541)=+EM0105                                                          
      A(  542)=-EM0085                                                          
      A(  543)=-EM0088                                                          
      A(  544)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  545)=-EM0106                                                          
      A(  546)=-EM0107                                                          
      A(  547)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   35)=+EM0127                                                          
      SL(   35)=-EM0082                                                         
      A(  548)=+EM0086                                                          
      A(  549)=+EM0089                                                          
      A(  550)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  551)=+EM0130                                                          
      A(  552)=+EM0132                                                          
      A(  553)=-EM0086                                                          
      A(  554)=-EM0089                                                          
      A(  555)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  556)=-EM0133                                                          
      A(  557)=-EM0134                                                          
      A(  558)=-EM0135                                                          
      B(   36)=+EM0128                                                          
      SL(   36)=-EM0083                                                         
      A(  559)=+EM0087                                                          
      A(  560)=+EM0090                                                          
      A(  561)=+EM0093                                                          
      EM0137=                                   -EM0037                         
      A(  562)=+EM0136                                                          
      A(  563)=+EM0137                                                          
      A(  564)=-EM0087                                                          
      A(  565)=-EM0090                                                          
      A(  566)=-EM0093                                                          
      EM0139=              +EM0102*EM0068-EM0099*EM0069                         
      EM0140=              +EM0096*EM0069-EM0102*EM0067                         
      EM0141=              +EM0099*EM0067-EM0096*EM0068                         
      A(  567)=-EM0139                                                          
      A(  568)=-EM0140                                                          
      A(  569)=-EM0141                                                          
      B(   37)=+EM0129                                                          
      SL(   37)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0088                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  748))                                             
      EQUIVALENCE(EM0011,GR(  749))                                             
      EQUIVALENCE(EM0012,GR(  750))                                             
      EQUIVALENCE(EM0013,GR(  751))                                             
      EQUIVALENCE(EM0014,GR(  752))                                             
      EQUIVALENCE(EM0015,GR(  753))                                             
      EQUIVALENCE(EM0016,GR(  754))                                             
      EQUIVALENCE(EM0017,GR(  755))                                             
      EQUIVALENCE(EM0018,GR(  756))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  244))                                             
      EQUIVALENCE(EM0025,GR(  245))                                             
      EQUIVALENCE(EM0020,GR(  246))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   79))                                             
      EQUIVALENCE(EM0029,GR(   80))                                             
      EQUIVALENCE(EM0030,GR(   81))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  241))                                             
      EQUIVALENCE(EM0032,GR(  242))                                             
      EQUIVALENCE(EM0033,GR(  243))                                             
      EQUIVALENCE(EM0034,GR(  244))                                             
      EQUIVALENCE(EM0035,GR(  245))                                             
      EQUIVALENCE(EM0036,GR(  246))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  332))                                             
      EQUIVALENCE(EM0038,GV(  325))                                             
      EQUIVALENCE(EM0039,GV(  324))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  793))                                             
      EQUIVALENCE(EM0041,GR(  794))                                             
      EQUIVALENCE(EM0042,GR(  795))                                             
      EQUIVALENCE(EM0043,GR(  796))                                             
      EQUIVALENCE(EM0044,GR(  797))                                             
      EQUIVALENCE(EM0045,GR(  798))                                             
      EQUIVALENCE(EM0046,GR(  799))                                             
      EQUIVALENCE(EM0047,GR(  800))                                             
      EQUIVALENCE(EM0048,GR(  801))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  238))                                             
      EQUIVALENCE(EM0055,GR(  239))                                             
      EQUIVALENCE(EM0050,GR(  240))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   73))                                             
      EQUIVALENCE(EM0059,GR(   74))                                             
      EQUIVALENCE(EM0060,GR(   75))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  235))                                             
      EQUIVALENCE(EM0062,GR(  236))                                             
      EQUIVALENCE(EM0063,GR(  237))                                             
      EQUIVALENCE(EM0064,GR(  238))                                             
      EQUIVALENCE(EM0065,GR(  239))                                             
      EQUIVALENCE(EM0066,GR(  240))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  311))                                             
      EQUIVALENCE(EM0068,GV(  301))                                             
      EQUIVALENCE(EM0069,GV(  300))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  570)=+EM0085                                                          
      A(  571)=+EM0088                                                          
      A(  572)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  573)=+EM0104                                                          
      A(  574)=+EM0105                                                          
      A(  575)=-EM0085                                                          
      A(  576)=-EM0088                                                          
      A(  577)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  578)=-EM0106                                                          
      A(  579)=-EM0107                                                          
      A(  580)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   38)=+EM0127                                                          
      SL(   38)=-EM0082                                                         
      A(  581)=+EM0086                                                          
      A(  582)=+EM0089                                                          
      A(  583)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  584)=+EM0130                                                          
      A(  585)=+EM0132                                                          
      A(  586)=-EM0086                                                          
      A(  587)=-EM0089                                                          
      A(  588)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  589)=-EM0133                                                          
      A(  590)=-EM0134                                                          
      A(  591)=-EM0135                                                          
      B(   39)=+EM0128                                                          
      SL(   39)=-EM0083                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0032                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  748))                                             
      EQUIVALENCE(EM0011,GR(  749))                                             
      EQUIVALENCE(EM0012,GR(  750))                                             
      EQUIVALENCE(EM0013,GR(  751))                                             
      EQUIVALENCE(EM0014,GR(  752))                                             
      EQUIVALENCE(EM0015,GR(  753))                                             
      EQUIVALENCE(EM0016,GR(  754))                                             
      EQUIVALENCE(EM0017,GR(  755))                                             
      EQUIVALENCE(EM0018,GR(  756))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  244))                                             
      EQUIVALENCE(EM0025,GR(  245))                                             
      EQUIVALENCE(EM0020,GR(  246))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   79))                                             
      EQUIVALENCE(EM0029,GR(   80))                                             
      EQUIVALENCE(EM0030,GR(   81))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  241))                                             
      EQUIVALENCE(EM0032,GR(  242))                                             
      EQUIVALENCE(EM0033,GR(  243))                                             
      EQUIVALENCE(EM0034,GR(  244))                                             
      EQUIVALENCE(EM0035,GR(  245))                                             
      EQUIVALENCE(EM0036,GR(  246))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  333))                                             
      EQUIVALENCE(EM0038,GV(  327))                                             
      EQUIVALENCE(EM0039,GV(  326))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  793))                                             
      EQUIVALENCE(EM0041,GR(  794))                                             
      EQUIVALENCE(EM0042,GR(  795))                                             
      EQUIVALENCE(EM0043,GR(  796))                                             
      EQUIVALENCE(EM0044,GR(  797))                                             
      EQUIVALENCE(EM0045,GR(  798))                                             
      EQUIVALENCE(EM0046,GR(  799))                                             
      EQUIVALENCE(EM0047,GR(  800))                                             
      EQUIVALENCE(EM0048,GR(  801))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  238))                                             
      EQUIVALENCE(EM0055,GR(  239))                                             
      EQUIVALENCE(EM0050,GR(  240))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   73))                                             
      EQUIVALENCE(EM0059,GR(   74))                                             
      EQUIVALENCE(EM0060,GR(   75))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  235))                                             
      EQUIVALENCE(EM0062,GR(  236))                                             
      EQUIVALENCE(EM0063,GR(  237))                                             
      EQUIVALENCE(EM0064,GR(  238))                                             
      EQUIVALENCE(EM0065,GR(  239))                                             
      EQUIVALENCE(EM0066,GR(  240))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  312))                                             
      EQUIVALENCE(EM0068,GV(  303))                                             
      EQUIVALENCE(EM0069,GV(  302))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0130,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  592)=+EM0085                                                          
      A(  593)=+EM0088                                                          
      A(  594)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  595)=+EM0104                                                          
      A(  596)=+EM0105                                                          
      A(  597)=-EM0085                                                          
      A(  598)=-EM0088                                                          
      A(  599)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  600)=-EM0106                                                          
      A(  601)=-EM0107                                                          
      A(  602)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   40)=+EM0127                                                          
      SL(   40)=-EM0082                                                         
      A(  603)=+EM0087                                                          
      A(  604)=+EM0090                                                          
      A(  605)=+EM0093                                                          
      EM0131=                                   -EM0037                         
      A(  606)=+EM0130                                                          
      A(  607)=+EM0131                                                          
      A(  608)=-EM0087                                                          
      A(  609)=-EM0090                                                          
      A(  610)=-EM0093                                                          
      EM0133=              +EM0102*EM0068-EM0099*EM0069                         
      EM0134=              +EM0096*EM0069-EM0102*EM0067                         
      EM0135=              +EM0099*EM0067-EM0096*EM0068                         
      A(  611)=-EM0133                                                          
      A(  612)=-EM0134                                                          
      A(  613)=-EM0135                                                          
      B(   41)=+EM0129                                                          
      SL(   41)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0028                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  838))                                             
      EQUIVALENCE(EM0011,GR(  839))                                             
      EQUIVALENCE(EM0012,GR(  840))                                             
      EQUIVALENCE(EM0013,GR(  841))                                             
      EQUIVALENCE(EM0014,GR(  842))                                             
      EQUIVALENCE(EM0015,GR(  843))                                             
      EQUIVALENCE(EM0016,GR(  844))                                             
      EQUIVALENCE(EM0017,GR(  845))                                             
      EQUIVALENCE(EM0018,GR(  846))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  232))                                             
      EQUIVALENCE(EM0025,GR(  233))                                             
      EQUIVALENCE(EM0020,GR(  234))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   67))                                             
      EQUIVALENCE(EM0029,GR(   68))                                             
      EQUIVALENCE(EM0030,GR(   69))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  229))                                             
      EQUIVALENCE(EM0032,GR(  230))                                             
      EQUIVALENCE(EM0033,GR(  231))                                             
      EQUIVALENCE(EM0034,GR(  232))                                             
      EQUIVALENCE(EM0035,GR(  233))                                             
      EQUIVALENCE(EM0036,GR(  234))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  294))                                             
      EQUIVALENCE(EM0038,GV(  287))                                             
      EQUIVALENCE(EM0039,GV(  286))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  793))                                             
      EQUIVALENCE(EM0041,GR(  794))                                             
      EQUIVALENCE(EM0042,GR(  795))                                             
      EQUIVALENCE(EM0043,GR(  796))                                             
      EQUIVALENCE(EM0044,GR(  797))                                             
      EQUIVALENCE(EM0045,GR(  798))                                             
      EQUIVALENCE(EM0046,GR(  799))                                             
      EQUIVALENCE(EM0047,GR(  800))                                             
      EQUIVALENCE(EM0048,GR(  801))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  238))                                             
      EQUIVALENCE(EM0055,GR(  239))                                             
      EQUIVALENCE(EM0050,GR(  240))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   73))                                             
      EQUIVALENCE(EM0059,GR(   74))                                             
      EQUIVALENCE(EM0060,GR(   75))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  235))                                             
      EQUIVALENCE(EM0062,GR(  236))                                             
      EQUIVALENCE(EM0063,GR(  237))                                             
      EQUIVALENCE(EM0064,GR(  238))                                             
      EQUIVALENCE(EM0065,GR(  239))                                             
      EQUIVALENCE(EM0066,GR(  240))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  313))                                             
      EQUIVALENCE(EM0068,GV(  305))                                             
      EQUIVALENCE(EM0069,GV(  304))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0130,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  614)=+EM0085                                                          
      A(  615)=+EM0088                                                          
      A(  616)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  617)=+EM0104                                                          
      A(  618)=+EM0105                                                          
      A(  619)=-EM0085                                                          
      A(  620)=-EM0088                                                          
      A(  621)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  622)=-EM0106                                                          
      A(  623)=-EM0107                                                          
      A(  624)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   42)=+EM0127                                                          
      SL(   42)=-EM0082                                                         
      A(  625)=+EM0087                                                          
      A(  626)=+EM0090                                                          
      A(  627)=+EM0093                                                          
      EM0131=                                   -EM0037                         
      A(  628)=+EM0130                                                          
      A(  629)=+EM0131                                                          
      A(  630)=-EM0087                                                          
      A(  631)=-EM0090                                                          
      A(  632)=-EM0093                                                          
      EM0133=              +EM0102*EM0068-EM0099*EM0069                         
      EM0134=              +EM0096*EM0069-EM0102*EM0067                         
      EM0135=              +EM0099*EM0067-EM0096*EM0068                         
      A(  633)=-EM0133                                                          
      A(  634)=-EM0134                                                          
      A(  635)=-EM0135                                                          
      B(   43)=+EM0129                                                          
      SL(   43)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0027                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  838))                                             
      EQUIVALENCE(EM0011,GR(  839))                                             
      EQUIVALENCE(EM0012,GR(  840))                                             
      EQUIVALENCE(EM0013,GR(  841))                                             
      EQUIVALENCE(EM0014,GR(  842))                                             
      EQUIVALENCE(EM0015,GR(  843))                                             
      EQUIVALENCE(EM0016,GR(  844))                                             
      EQUIVALENCE(EM0017,GR(  845))                                             
      EQUIVALENCE(EM0018,GR(  846))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  232))                                             
      EQUIVALENCE(EM0025,GR(  233))                                             
      EQUIVALENCE(EM0020,GR(  234))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   67))                                             
      EQUIVALENCE(EM0029,GR(   68))                                             
      EQUIVALENCE(EM0030,GR(   69))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  229))                                             
      EQUIVALENCE(EM0032,GR(  230))                                             
      EQUIVALENCE(EM0033,GR(  231))                                             
      EQUIVALENCE(EM0034,GR(  232))                                             
      EQUIVALENCE(EM0035,GR(  233))                                             
      EQUIVALENCE(EM0036,GR(  234))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  295))                                             
      EQUIVALENCE(EM0038,GV(  289))                                             
      EQUIVALENCE(EM0039,GV(  288))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  793))                                             
      EQUIVALENCE(EM0041,GR(  794))                                             
      EQUIVALENCE(EM0042,GR(  795))                                             
      EQUIVALENCE(EM0043,GR(  796))                                             
      EQUIVALENCE(EM0044,GR(  797))                                             
      EQUIVALENCE(EM0045,GR(  798))                                             
      EQUIVALENCE(EM0046,GR(  799))                                             
      EQUIVALENCE(EM0047,GR(  800))                                             
      EQUIVALENCE(EM0048,GR(  801))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  238))                                             
      EQUIVALENCE(EM0055,GR(  239))                                             
      EQUIVALENCE(EM0050,GR(  240))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   73))                                             
      EQUIVALENCE(EM0059,GR(   74))                                             
      EQUIVALENCE(EM0060,GR(   75))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  235))                                             
      EQUIVALENCE(EM0062,GR(  236))                                             
      EQUIVALENCE(EM0063,GR(  237))                                             
      EQUIVALENCE(EM0064,GR(  238))                                             
      EQUIVALENCE(EM0065,GR(  239))                                             
      EQUIVALENCE(EM0066,GR(  240))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  314))                                             
      EQUIVALENCE(EM0068,GV(  307))                                             
      EQUIVALENCE(EM0069,GV(  306))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
      EQUIVALENCE(EM0136,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  636)=+EM0085                                                          
      A(  637)=+EM0088                                                          
      A(  638)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  639)=+EM0104                                                          
      A(  640)=+EM0105                                                          
      A(  641)=-EM0085                                                          
      A(  642)=-EM0088                                                          
      A(  643)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  644)=-EM0106                                                          
      A(  645)=-EM0107                                                          
      A(  646)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   44)=+EM0127                                                          
      SL(   44)=-EM0082                                                         
      A(  647)=+EM0086                                                          
      A(  648)=+EM0089                                                          
      A(  649)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  650)=+EM0130                                                          
      A(  651)=+EM0132                                                          
      A(  652)=-EM0086                                                          
      A(  653)=-EM0089                                                          
      A(  654)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  655)=-EM0133                                                          
      A(  656)=-EM0134                                                          
      A(  657)=-EM0135                                                          
      B(   45)=+EM0128                                                          
      SL(   45)=-EM0083                                                         
      A(  658)=+EM0087                                                          
      A(  659)=+EM0090                                                          
      A(  660)=+EM0093                                                          
      EM0137=                                   -EM0037                         
      A(  661)=+EM0136                                                          
      A(  662)=+EM0137                                                          
      A(  663)=-EM0087                                                          
      A(  664)=-EM0090                                                          
      A(  665)=-EM0093                                                          
      EM0139=              +EM0102*EM0068-EM0099*EM0069                         
      EM0140=              +EM0096*EM0069-EM0102*EM0067                         
      EM0141=              +EM0099*EM0067-EM0096*EM0068                         
      A(  666)=-EM0139                                                          
      A(  667)=-EM0140                                                          
      A(  668)=-EM0141                                                          
      B(   46)=+EM0129                                                          
      SL(   46)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0090                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  875))                                             
      EQUIVALENCE(EM0011,GR(  876))                                             
      EQUIVALENCE(EM0012,GR(  877))                                             
      EQUIVALENCE(EM0013,GR(  878))                                             
      EQUIVALENCE(EM0014,GR(  879))                                             
      EQUIVALENCE(EM0015,GR(  880))                                             
      EQUIVALENCE(EM0016,GR(  881))                                             
      EQUIVALENCE(EM0017,GR(  882))                                             
      EQUIVALENCE(EM0018,GR(  883))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  226))                                             
      EQUIVALENCE(EM0025,GR(  227))                                             
      EQUIVALENCE(EM0020,GR(  228))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   61))                                             
      EQUIVALENCE(EM0029,GR(   62))                                             
      EQUIVALENCE(EM0030,GR(   63))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  223))                                             
      EQUIVALENCE(EM0032,GR(  224))                                             
      EQUIVALENCE(EM0033,GR(  225))                                             
      EQUIVALENCE(EM0034,GR(  226))                                             
      EQUIVALENCE(EM0035,GR(  227))                                             
      EQUIVALENCE(EM0036,GR(  228))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  281))                                             
      EQUIVALENCE(EM0038,GV(  272))                                             
      EQUIVALENCE(EM0039,GV(  271))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  793))                                             
      EQUIVALENCE(EM0041,GR(  794))                                             
      EQUIVALENCE(EM0042,GR(  795))                                             
      EQUIVALENCE(EM0043,GR(  796))                                             
      EQUIVALENCE(EM0044,GR(  797))                                             
      EQUIVALENCE(EM0045,GR(  798))                                             
      EQUIVALENCE(EM0046,GR(  799))                                             
      EQUIVALENCE(EM0047,GR(  800))                                             
      EQUIVALENCE(EM0048,GR(  801))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  238))                                             
      EQUIVALENCE(EM0055,GR(  239))                                             
      EQUIVALENCE(EM0050,GR(  240))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   73))                                             
      EQUIVALENCE(EM0059,GR(   74))                                             
      EQUIVALENCE(EM0060,GR(   75))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  235))                                             
      EQUIVALENCE(EM0062,GR(  236))                                             
      EQUIVALENCE(EM0063,GR(  237))                                             
      EQUIVALENCE(EM0064,GR(  238))                                             
      EQUIVALENCE(EM0065,GR(  239))                                             
      EQUIVALENCE(EM0066,GR(  240))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  315))                                             
      EQUIVALENCE(EM0068,GV(  309))                                             
      EQUIVALENCE(EM0069,GV(  308))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  669)=+EM0085                                                          
      A(  670)=+EM0088                                                          
      A(  671)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  672)=+EM0104                                                          
      A(  673)=+EM0105                                                          
      A(  674)=-EM0085                                                          
      A(  675)=-EM0088                                                          
      A(  676)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  677)=-EM0106                                                          
      A(  678)=-EM0107                                                          
      A(  679)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   47)=+EM0127                                                          
      SL(   47)=-EM0082                                                         
      A(  680)=+EM0086                                                          
      A(  681)=+EM0089                                                          
      A(  682)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  683)=+EM0130                                                          
      A(  684)=+EM0132                                                          
      A(  685)=-EM0086                                                          
      A(  686)=-EM0089                                                          
      A(  687)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  688)=-EM0133                                                          
      A(  689)=-EM0134                                                          
      A(  690)=-EM0135                                                          
      B(   48)=+EM0128                                                          
      SL(   48)=-EM0083                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0030                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  838))                                             
      EQUIVALENCE(EM0011,GR(  839))                                             
      EQUIVALENCE(EM0012,GR(  840))                                             
      EQUIVALENCE(EM0013,GR(  841))                                             
      EQUIVALENCE(EM0014,GR(  842))                                             
      EQUIVALENCE(EM0015,GR(  843))                                             
      EQUIVALENCE(EM0016,GR(  844))                                             
      EQUIVALENCE(EM0017,GR(  845))                                             
      EQUIVALENCE(EM0018,GR(  846))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  232))                                             
      EQUIVALENCE(EM0025,GR(  233))                                             
      EQUIVALENCE(EM0020,GR(  234))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   67))                                             
      EQUIVALENCE(EM0029,GR(   68))                                             
      EQUIVALENCE(EM0030,GR(   69))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  229))                                             
      EQUIVALENCE(EM0032,GR(  230))                                             
      EQUIVALENCE(EM0033,GR(  231))                                             
      EQUIVALENCE(EM0034,GR(  232))                                             
      EQUIVALENCE(EM0035,GR(  233))                                             
      EQUIVALENCE(EM0036,GR(  234))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  296))                                             
      EQUIVALENCE(EM0038,GV(  291))                                             
      EQUIVALENCE(EM0039,GV(  290))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  875))                                             
      EQUIVALENCE(EM0041,GR(  876))                                             
      EQUIVALENCE(EM0042,GR(  877))                                             
      EQUIVALENCE(EM0043,GR(  878))                                             
      EQUIVALENCE(EM0044,GR(  879))                                             
      EQUIVALENCE(EM0045,GR(  880))                                             
      EQUIVALENCE(EM0046,GR(  881))                                             
      EQUIVALENCE(EM0047,GR(  882))                                             
      EQUIVALENCE(EM0048,GR(  883))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  226))                                             
      EQUIVALENCE(EM0055,GR(  227))                                             
      EQUIVALENCE(EM0050,GR(  228))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   61))                                             
      EQUIVALENCE(EM0059,GR(   62))                                             
      EQUIVALENCE(EM0060,GR(   63))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  223))                                             
      EQUIVALENCE(EM0062,GR(  224))                                             
      EQUIVALENCE(EM0063,GR(  225))                                             
      EQUIVALENCE(EM0064,GR(  226))                                             
      EQUIVALENCE(EM0065,GR(  227))                                             
      EQUIVALENCE(EM0066,GR(  228))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  282))                                             
      EQUIVALENCE(EM0068,GV(  274))                                             
      EQUIVALENCE(EM0069,GV(  273))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0105,EM0037)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0130,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  691)=+EM0086                                                          
      A(  692)=+EM0089                                                          
      A(  693)=+EM0092                                                          
      EM0103=                                   -EM0039                         
      A(  694)=+EM0103                                                          
      A(  695)=+EM0105                                                          
      A(  696)=-EM0086                                                          
      A(  697)=-EM0089                                                          
      A(  698)=-EM0092                                                          
      EM0106=              +EM0101*EM0068-EM0098*EM0069                         
      EM0107=              +EM0095*EM0069-EM0101*EM0067                         
      EM0108=              +EM0098*EM0067-EM0095*EM0068                         
      A(  699)=-EM0106                                                          
      A(  700)=-EM0107                                                          
      A(  701)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   49)=+EM0128                                                          
      SL(   49)=-EM0083                                                         
      A(  702)=+EM0087                                                          
      A(  703)=+EM0090                                                          
      A(  704)=+EM0093                                                          
      EM0131=                                   -EM0037                         
      A(  705)=+EM0130                                                          
      A(  706)=+EM0131                                                          
      A(  707)=-EM0087                                                          
      A(  708)=-EM0090                                                          
      A(  709)=-EM0093                                                          
      EM0133=              +EM0102*EM0068-EM0099*EM0069                         
      EM0134=              +EM0096*EM0069-EM0102*EM0067                         
      EM0135=              +EM0099*EM0067-EM0096*EM0068                         
      A(  710)=-EM0133                                                          
      A(  711)=-EM0134                                                          
      A(  712)=-EM0135                                                          
      B(   50)=+EM0129                                                          
      SL(   50)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0029                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  838))                                             
      EQUIVALENCE(EM0011,GR(  839))                                             
      EQUIVALENCE(EM0012,GR(  840))                                             
      EQUIVALENCE(EM0013,GR(  841))                                             
      EQUIVALENCE(EM0014,GR(  842))                                             
      EQUIVALENCE(EM0015,GR(  843))                                             
      EQUIVALENCE(EM0016,GR(  844))                                             
      EQUIVALENCE(EM0017,GR(  845))                                             
      EQUIVALENCE(EM0018,GR(  846))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  232))                                             
      EQUIVALENCE(EM0025,GR(  233))                                             
      EQUIVALENCE(EM0020,GR(  234))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   67))                                             
      EQUIVALENCE(EM0029,GR(   68))                                             
      EQUIVALENCE(EM0030,GR(   69))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  229))                                             
      EQUIVALENCE(EM0032,GR(  230))                                             
      EQUIVALENCE(EM0033,GR(  231))                                             
      EQUIVALENCE(EM0034,GR(  232))                                             
      EQUIVALENCE(EM0035,GR(  233))                                             
      EQUIVALENCE(EM0036,GR(  234))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  297))                                             
      EQUIVALENCE(EM0038,GV(  293))                                             
      EQUIVALENCE(EM0039,GV(  292))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  875))                                             
      EQUIVALENCE(EM0041,GR(  876))                                             
      EQUIVALENCE(EM0042,GR(  877))                                             
      EQUIVALENCE(EM0043,GR(  878))                                             
      EQUIVALENCE(EM0044,GR(  879))                                             
      EQUIVALENCE(EM0045,GR(  880))                                             
      EQUIVALENCE(EM0046,GR(  881))                                             
      EQUIVALENCE(EM0047,GR(  882))                                             
      EQUIVALENCE(EM0048,GR(  883))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  226))                                             
      EQUIVALENCE(EM0055,GR(  227))                                             
      EQUIVALENCE(EM0050,GR(  228))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   61))                                             
      EQUIVALENCE(EM0059,GR(   62))                                             
      EQUIVALENCE(EM0060,GR(   63))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  223))                                             
      EQUIVALENCE(EM0062,GR(  224))                                             
      EQUIVALENCE(EM0063,GR(  225))                                             
      EQUIVALENCE(EM0064,GR(  226))                                             
      EQUIVALENCE(EM0065,GR(  227))                                             
      EQUIVALENCE(EM0066,GR(  228))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  283))                                             
      EQUIVALENCE(EM0068,GV(  276))                                             
      EQUIVALENCE(EM0069,GV(  275))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
      EQUIVALENCE(EM0136,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  713)=+EM0085                                                          
      A(  714)=+EM0088                                                          
      A(  715)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  716)=+EM0104                                                          
      A(  717)=+EM0105                                                          
      A(  718)=-EM0085                                                          
      A(  719)=-EM0088                                                          
      A(  720)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  721)=-EM0106                                                          
      A(  722)=-EM0107                                                          
      A(  723)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   51)=+EM0127                                                          
      SL(   51)=-EM0082                                                         
      A(  724)=+EM0086                                                          
      A(  725)=+EM0089                                                          
      A(  726)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  727)=+EM0130                                                          
      A(  728)=+EM0132                                                          
      A(  729)=-EM0086                                                          
      A(  730)=-EM0089                                                          
      A(  731)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  732)=-EM0133                                                          
      A(  733)=-EM0134                                                          
      A(  734)=-EM0135                                                          
      B(   52)=+EM0128                                                          
      SL(   52)=-EM0083                                                         
      A(  735)=+EM0087                                                          
      A(  736)=+EM0090                                                          
      A(  737)=+EM0093                                                          
      EM0137=                                   -EM0037                         
      A(  738)=+EM0136                                                          
      A(  739)=+EM0137                                                          
      A(  740)=-EM0087                                                          
      A(  741)=-EM0090                                                          
      A(  742)=-EM0093                                                          
      EM0139=              +EM0102*EM0068-EM0099*EM0069                         
      EM0140=              +EM0096*EM0069-EM0102*EM0067                         
      EM0141=              +EM0099*EM0067-EM0096*EM0068                         
      A(  743)=-EM0139                                                          
      A(  744)=-EM0140                                                          
      A(  745)=-EM0141                                                          
      B(   53)=+EM0129                                                          
      SL(   53)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0095                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  920))                                             
      EQUIVALENCE(EM0011,GR(  921))                                             
      EQUIVALENCE(EM0012,GR(  922))                                             
      EQUIVALENCE(EM0013,GR(  923))                                             
      EQUIVALENCE(EM0014,GR(  924))                                             
      EQUIVALENCE(EM0015,GR(  925))                                             
      EQUIVALENCE(EM0016,GR(  926))                                             
      EQUIVALENCE(EM0017,GR(  927))                                             
      EQUIVALENCE(EM0018,GR(  928))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  208))                                             
      EQUIVALENCE(EM0025,GR(  209))                                             
      EQUIVALENCE(EM0020,GR(  210))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   43))                                             
      EQUIVALENCE(EM0029,GR(   44))                                             
      EQUIVALENCE(EM0030,GR(   45))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  205))                                             
      EQUIVALENCE(EM0032,GR(  206))                                             
      EQUIVALENCE(EM0033,GR(  207))                                             
      EQUIVALENCE(EM0034,GR(  208))                                             
      EQUIVALENCE(EM0035,GR(  209))                                             
      EQUIVALENCE(EM0036,GR(  210))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  243))                                             
      EQUIVALENCE(EM0038,GV(  236))                                             
      EQUIVALENCE(EM0039,GV(  235))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  937))                                             
      EQUIVALENCE(EM0041,GR(  938))                                             
      EQUIVALENCE(EM0042,GR(  939))                                             
      EQUIVALENCE(EM0043,GR(  940))                                             
      EQUIVALENCE(EM0044,GR(  941))                                             
      EQUIVALENCE(EM0045,GR(  942))                                             
      EQUIVALENCE(EM0046,GR(  943))                                             
      EQUIVALENCE(EM0047,GR(  944))                                             
      EQUIVALENCE(EM0048,GR(  945))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  304))                                             
      EQUIVALENCE(EM0055,GR(  305))                                             
      EQUIVALENCE(EM0050,GR(  306))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(  139))                                             
      EQUIVALENCE(EM0059,GR(  140))                                             
      EQUIVALENCE(EM0060,GR(  141))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  301))                                             
      EQUIVALENCE(EM0062,GR(  302))                                             
      EQUIVALENCE(EM0063,GR(  303))                                             
      EQUIVALENCE(EM0064,GR(  304))                                             
      EQUIVALENCE(EM0065,GR(  305))                                             
      EQUIVALENCE(EM0066,GR(  306))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  451))                                             
      EQUIVALENCE(EM0068,GV(  452))                                             
      EQUIVALENCE(EM0069,GV(  453))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  746)=+EM0085                                                          
      A(  747)=+EM0088                                                          
      A(  748)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  749)=+EM0104                                                          
      A(  750)=+EM0105                                                          
      A(  751)=-EM0085                                                          
      A(  752)=-EM0088                                                          
      A(  753)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  754)=-EM0106                                                          
      A(  755)=-EM0107                                                          
      A(  756)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   54)=+EM0127                                                          
      SL(   54)=-EM0082                                                         
      A(  757)=+EM0086                                                          
      A(  758)=+EM0089                                                          
      A(  759)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  760)=+EM0130                                                          
      A(  761)=+EM0132                                                          
      A(  762)=-EM0086                                                          
      A(  763)=-EM0089                                                          
      A(  764)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  765)=-EM0133                                                          
      A(  766)=-EM0134                                                          
      A(  767)=-EM0135                                                          
      B(   55)=+EM0128                                                          
      SL(   55)=-EM0083                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0024                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  920))                                             
      EQUIVALENCE(EM0011,GR(  921))                                             
      EQUIVALENCE(EM0012,GR(  922))                                             
      EQUIVALENCE(EM0013,GR(  923))                                             
      EQUIVALENCE(EM0014,GR(  924))                                             
      EQUIVALENCE(EM0015,GR(  925))                                             
      EQUIVALENCE(EM0016,GR(  926))                                             
      EQUIVALENCE(EM0017,GR(  927))                                             
      EQUIVALENCE(EM0018,GR(  928))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  208))                                             
      EQUIVALENCE(EM0025,GR(  209))                                             
      EQUIVALENCE(EM0020,GR(  210))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   43))                                             
      EQUIVALENCE(EM0029,GR(   44))                                             
      EQUIVALENCE(EM0030,GR(   45))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  205))                                             
      EQUIVALENCE(EM0032,GR(  206))                                             
      EQUIVALENCE(EM0033,GR(  207))                                             
      EQUIVALENCE(EM0034,GR(  208))                                             
      EQUIVALENCE(EM0035,GR(  209))                                             
      EQUIVALENCE(EM0036,GR(  210))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  244))                                             
      EQUIVALENCE(EM0038,GV(  238))                                             
      EQUIVALENCE(EM0039,GV(  237))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  962))                                             
      EQUIVALENCE(EM0041,GR(  963))                                             
      EQUIVALENCE(EM0042,GR(  964))                                             
      EQUIVALENCE(EM0043,GR(  965))                                             
      EQUIVALENCE(EM0044,GR(  966))                                             
      EQUIVALENCE(EM0045,GR(  967))                                             
      EQUIVALENCE(EM0046,GR(  968))                                             
      EQUIVALENCE(EM0047,GR(  969))                                             
      EQUIVALENCE(EM0048,GR(  970))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  220))                                             
      EQUIVALENCE(EM0055,GR(  221))                                             
      EQUIVALENCE(EM0050,GR(  222))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   55))                                             
      EQUIVALENCE(EM0059,GR(   56))                                             
      EQUIVALENCE(EM0060,GR(   57))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  217))                                             
      EQUIVALENCE(EM0062,GR(  218))                                             
      EQUIVALENCE(EM0063,GR(  219))                                             
      EQUIVALENCE(EM0064,GR(  220))                                             
      EQUIVALENCE(EM0065,GR(  221))                                             
      EQUIVALENCE(EM0066,GR(  222))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  267))                                             
      EQUIVALENCE(EM0068,GV(  260))                                             
      EQUIVALENCE(EM0069,GV(  259))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0105,EM0037)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0130,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  768)=+EM0086                                                          
      A(  769)=+EM0089                                                          
      A(  770)=+EM0092                                                          
      EM0103=                                   -EM0039                         
      A(  771)=+EM0103                                                          
      A(  772)=+EM0105                                                          
      A(  773)=-EM0086                                                          
      A(  774)=-EM0089                                                          
      A(  775)=-EM0092                                                          
      EM0106=              +EM0101*EM0068-EM0098*EM0069                         
      EM0107=              +EM0095*EM0069-EM0101*EM0067                         
      EM0108=              +EM0098*EM0067-EM0095*EM0068                         
      A(  776)=-EM0106                                                          
      A(  777)=-EM0107                                                          
      A(  778)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   56)=+EM0128                                                          
      SL(   56)=-EM0083                                                         
      A(  779)=+EM0087                                                          
      A(  780)=+EM0090                                                          
      A(  781)=+EM0093                                                          
      EM0131=                                   -EM0037                         
      A(  782)=+EM0130                                                          
      A(  783)=+EM0131                                                          
      A(  784)=-EM0087                                                          
      A(  785)=-EM0090                                                          
      A(  786)=-EM0093                                                          
      EM0133=              +EM0102*EM0068-EM0099*EM0069                         
      EM0134=              +EM0096*EM0069-EM0102*EM0067                         
      EM0135=              +EM0099*EM0067-EM0096*EM0068                         
      A(  787)=-EM0133                                                          
      A(  788)=-EM0134                                                          
      A(  789)=-EM0135                                                          
      B(   57)=+EM0129                                                          
      SL(   57)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0023                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  962))                                             
      EQUIVALENCE(EM0011,GR(  963))                                             
      EQUIVALENCE(EM0012,GR(  964))                                             
      EQUIVALENCE(EM0013,GR(  965))                                             
      EQUIVALENCE(EM0014,GR(  966))                                             
      EQUIVALENCE(EM0015,GR(  967))                                             
      EQUIVALENCE(EM0016,GR(  968))                                             
      EQUIVALENCE(EM0017,GR(  969))                                             
      EQUIVALENCE(EM0018,GR(  970))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  220))                                             
      EQUIVALENCE(EM0025,GR(  221))                                             
      EQUIVALENCE(EM0020,GR(  222))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   55))                                             
      EQUIVALENCE(EM0029,GR(   56))                                             
      EQUIVALENCE(EM0030,GR(   57))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  217))                                             
      EQUIVALENCE(EM0032,GR(  218))                                             
      EQUIVALENCE(EM0033,GR(  219))                                             
      EQUIVALENCE(EM0034,GR(  220))                                             
      EQUIVALENCE(EM0035,GR(  221))                                             
      EQUIVALENCE(EM0036,GR(  222))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  268))                                             
      EQUIVALENCE(EM0038,GV(  262))                                             
      EQUIVALENCE(EM0039,GV(  261))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  920))                                             
      EQUIVALENCE(EM0041,GR(  921))                                             
      EQUIVALENCE(EM0042,GR(  922))                                             
      EQUIVALENCE(EM0043,GR(  923))                                             
      EQUIVALENCE(EM0044,GR(  924))                                             
      EQUIVALENCE(EM0045,GR(  925))                                             
      EQUIVALENCE(EM0046,GR(  926))                                             
      EQUIVALENCE(EM0047,GR(  927))                                             
      EQUIVALENCE(EM0048,GR(  928))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  208))                                             
      EQUIVALENCE(EM0055,GR(  209))                                             
      EQUIVALENCE(EM0050,GR(  210))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   43))                                             
      EQUIVALENCE(EM0059,GR(   44))                                             
      EQUIVALENCE(EM0060,GR(   45))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  205))                                             
      EQUIVALENCE(EM0062,GR(  206))                                             
      EQUIVALENCE(EM0063,GR(  207))                                             
      EQUIVALENCE(EM0064,GR(  208))                                             
      EQUIVALENCE(EM0065,GR(  209))                                             
      EQUIVALENCE(EM0066,GR(  210))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  245))                                             
      EQUIVALENCE(EM0068,GV(  240))                                             
      EQUIVALENCE(EM0069,GV(  239))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
      EQUIVALENCE(EM0136,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  790)=+EM0085                                                          
      A(  791)=+EM0088                                                          
      A(  792)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  793)=+EM0104                                                          
      A(  794)=+EM0105                                                          
      A(  795)=-EM0085                                                          
      A(  796)=-EM0088                                                          
      A(  797)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  798)=-EM0106                                                          
      A(  799)=-EM0107                                                          
      A(  800)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   58)=+EM0127                                                          
      SL(   58)=-EM0082                                                         
      A(  801)=+EM0086                                                          
      A(  802)=+EM0089                                                          
      A(  803)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  804)=+EM0130                                                          
      A(  805)=+EM0132                                                          
      A(  806)=-EM0086                                                          
      A(  807)=-EM0089                                                          
      A(  808)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  809)=-EM0133                                                          
      A(  810)=-EM0134                                                          
      A(  811)=-EM0135                                                          
      B(   59)=+EM0128                                                          
      SL(   59)=-EM0083                                                         
      A(  812)=+EM0087                                                          
      A(  813)=+EM0090                                                          
      A(  814)=+EM0093                                                          
      EM0137=                                   -EM0037                         
      A(  815)=+EM0136                                                          
      A(  816)=+EM0137                                                          
      A(  817)=-EM0087                                                          
      A(  818)=-EM0090                                                          
      A(  819)=-EM0093                                                          
      EM0139=              +EM0102*EM0068-EM0099*EM0069                         
      EM0140=              +EM0096*EM0069-EM0102*EM0067                         
      EM0141=              +EM0099*EM0067-EM0096*EM0068                         
      A(  820)=-EM0139                                                          
      A(  821)=-EM0140                                                          
      A(  822)=-EM0141                                                          
      B(   60)=+EM0129                                                          
      SL(   60)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0087                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  920))                                             
      EQUIVALENCE(EM0011,GR(  921))                                             
      EQUIVALENCE(EM0012,GR(  922))                                             
      EQUIVALENCE(EM0013,GR(  923))                                             
      EQUIVALENCE(EM0014,GR(  924))                                             
      EQUIVALENCE(EM0015,GR(  925))                                             
      EQUIVALENCE(EM0016,GR(  926))                                             
      EQUIVALENCE(EM0017,GR(  927))                                             
      EQUIVALENCE(EM0018,GR(  928))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  208))                                             
      EQUIVALENCE(EM0025,GR(  209))                                             
      EQUIVALENCE(EM0020,GR(  210))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   43))                                             
      EQUIVALENCE(EM0029,GR(   44))                                             
      EQUIVALENCE(EM0030,GR(   45))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  205))                                             
      EQUIVALENCE(EM0032,GR(  206))                                             
      EQUIVALENCE(EM0033,GR(  207))                                             
      EQUIVALENCE(EM0034,GR(  208))                                             
      EQUIVALENCE(EM0035,GR(  209))                                             
      EQUIVALENCE(EM0036,GR(  210))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  246))                                             
      EQUIVALENCE(EM0038,GV(  242))                                             
      EQUIVALENCE(EM0039,GV(  241))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  999))                                             
      EQUIVALENCE(EM0041,GR( 1000))                                             
      EQUIVALENCE(EM0042,GR( 1001))                                             
      EQUIVALENCE(EM0043,GR( 1002))                                             
      EQUIVALENCE(EM0044,GR( 1003))                                             
      EQUIVALENCE(EM0045,GR( 1004))                                             
      EQUIVALENCE(EM0046,GR( 1005))                                             
      EQUIVALENCE(EM0047,GR( 1006))                                             
      EQUIVALENCE(EM0048,GR( 1007))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  202))                                             
      EQUIVALENCE(EM0055,GR(  203))                                             
      EQUIVALENCE(EM0050,GR(  204))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   37))                                             
      EQUIVALENCE(EM0059,GR(   38))                                             
      EQUIVALENCE(EM0060,GR(   39))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  199))                                             
      EQUIVALENCE(EM0062,GR(  200))                                             
      EQUIVALENCE(EM0063,GR(  201))                                             
      EQUIVALENCE(EM0064,GR(  202))                                             
      EQUIVALENCE(EM0065,GR(  203))                                             
      EQUIVALENCE(EM0066,GR(  204))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  229))                                             
      EQUIVALENCE(EM0068,GV(  218))                                             
      EQUIVALENCE(EM0069,GV(  217))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  823)=+EM0085                                                          
      A(  824)=+EM0088                                                          
      A(  825)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  826)=+EM0104                                                          
      A(  827)=+EM0105                                                          
      A(  828)=-EM0085                                                          
      A(  829)=-EM0088                                                          
      A(  830)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  831)=-EM0106                                                          
      A(  832)=-EM0107                                                          
      A(  833)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   61)=+EM0127                                                          
      SL(   61)=-EM0082                                                         
      A(  834)=+EM0086                                                          
      A(  835)=+EM0089                                                          
      A(  836)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  837)=+EM0130                                                          
      A(  838)=+EM0132                                                          
      A(  839)=-EM0086                                                          
      A(  840)=-EM0089                                                          
      A(  841)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  842)=-EM0133                                                          
      A(  843)=-EM0134                                                          
      A(  844)=-EM0135                                                          
      B(   62)=+EM0128                                                          
      SL(   62)=-EM0083                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0022                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  962))                                             
      EQUIVALENCE(EM0011,GR(  963))                                             
      EQUIVALENCE(EM0012,GR(  964))                                             
      EQUIVALENCE(EM0013,GR(  965))                                             
      EQUIVALENCE(EM0014,GR(  966))                                             
      EQUIVALENCE(EM0015,GR(  967))                                             
      EQUIVALENCE(EM0016,GR(  968))                                             
      EQUIVALENCE(EM0017,GR(  969))                                             
      EQUIVALENCE(EM0018,GR(  970))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  220))                                             
      EQUIVALENCE(EM0025,GR(  221))                                             
      EQUIVALENCE(EM0020,GR(  222))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   55))                                             
      EQUIVALENCE(EM0029,GR(   56))                                             
      EQUIVALENCE(EM0030,GR(   57))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  217))                                             
      EQUIVALENCE(EM0032,GR(  218))                                             
      EQUIVALENCE(EM0033,GR(  219))                                             
      EQUIVALENCE(EM0034,GR(  220))                                             
      EQUIVALENCE(EM0035,GR(  221))                                             
      EQUIVALENCE(EM0036,GR(  222))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  269))                                             
      EQUIVALENCE(EM0038,GV(  264))                                             
      EQUIVALENCE(EM0039,GV(  263))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  999))                                             
      EQUIVALENCE(EM0041,GR( 1000))                                             
      EQUIVALENCE(EM0042,GR( 1001))                                             
      EQUIVALENCE(EM0043,GR( 1002))                                             
      EQUIVALENCE(EM0044,GR( 1003))                                             
      EQUIVALENCE(EM0045,GR( 1004))                                             
      EQUIVALENCE(EM0046,GR( 1005))                                             
      EQUIVALENCE(EM0047,GR( 1006))                                             
      EQUIVALENCE(EM0048,GR( 1007))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  202))                                             
      EQUIVALENCE(EM0055,GR(  203))                                             
      EQUIVALENCE(EM0050,GR(  204))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   37))                                             
      EQUIVALENCE(EM0059,GR(   38))                                             
      EQUIVALENCE(EM0060,GR(   39))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  199))                                             
      EQUIVALENCE(EM0062,GR(  200))                                             
      EQUIVALENCE(EM0063,GR(  201))                                             
      EQUIVALENCE(EM0064,GR(  202))                                             
      EQUIVALENCE(EM0065,GR(  203))                                             
      EQUIVALENCE(EM0066,GR(  204))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  230))                                             
      EQUIVALENCE(EM0068,GV(  220))                                             
      EQUIVALENCE(EM0069,GV(  219))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0130,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  845)=+EM0085                                                          
      A(  846)=+EM0088                                                          
      A(  847)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  848)=+EM0104                                                          
      A(  849)=+EM0105                                                          
      A(  850)=-EM0085                                                          
      A(  851)=-EM0088                                                          
      A(  852)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  853)=-EM0106                                                          
      A(  854)=-EM0107                                                          
      A(  855)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   63)=+EM0127                                                          
      SL(   63)=-EM0082                                                         
      A(  856)=+EM0087                                                          
      A(  857)=+EM0090                                                          
      A(  858)=+EM0093                                                          
      EM0131=                                   -EM0037                         
      A(  859)=+EM0130                                                          
      A(  860)=+EM0131                                                          
      A(  861)=-EM0087                                                          
      A(  862)=-EM0090                                                          
      A(  863)=-EM0093                                                          
      EM0133=              +EM0102*EM0068-EM0099*EM0069                         
      EM0134=              +EM0096*EM0069-EM0102*EM0067                         
      EM0135=              +EM0099*EM0067-EM0096*EM0068                         
      A(  864)=-EM0133                                                          
      A(  865)=-EM0134                                                          
      A(  866)=-EM0135                                                          
      B(   64)=+EM0129                                                          
      SL(   64)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0021                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  962))                                             
      EQUIVALENCE(EM0011,GR(  963))                                             
      EQUIVALENCE(EM0012,GR(  964))                                             
      EQUIVALENCE(EM0013,GR(  965))                                             
      EQUIVALENCE(EM0014,GR(  966))                                             
      EQUIVALENCE(EM0015,GR(  967))                                             
      EQUIVALENCE(EM0016,GR(  968))                                             
      EQUIVALENCE(EM0017,GR(  969))                                             
      EQUIVALENCE(EM0018,GR(  970))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  220))                                             
      EQUIVALENCE(EM0025,GR(  221))                                             
      EQUIVALENCE(EM0020,GR(  222))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   55))                                             
      EQUIVALENCE(EM0029,GR(   56))                                             
      EQUIVALENCE(EM0030,GR(   57))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  217))                                             
      EQUIVALENCE(EM0032,GR(  218))                                             
      EQUIVALENCE(EM0033,GR(  219))                                             
      EQUIVALENCE(EM0034,GR(  220))                                             
      EQUIVALENCE(EM0035,GR(  221))                                             
      EQUIVALENCE(EM0036,GR(  222))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  270))                                             
      EQUIVALENCE(EM0038,GV(  266))                                             
      EQUIVALENCE(EM0039,GV(  265))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR(  999))                                             
      EQUIVALENCE(EM0041,GR( 1000))                                             
      EQUIVALENCE(EM0042,GR( 1001))                                             
      EQUIVALENCE(EM0043,GR( 1002))                                             
      EQUIVALENCE(EM0044,GR( 1003))                                             
      EQUIVALENCE(EM0045,GR( 1004))                                             
      EQUIVALENCE(EM0046,GR( 1005))                                             
      EQUIVALENCE(EM0047,GR( 1006))                                             
      EQUIVALENCE(EM0048,GR( 1007))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  202))                                             
      EQUIVALENCE(EM0055,GR(  203))                                             
      EQUIVALENCE(EM0050,GR(  204))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   37))                                             
      EQUIVALENCE(EM0059,GR(   38))                                             
      EQUIVALENCE(EM0060,GR(   39))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  199))                                             
      EQUIVALENCE(EM0062,GR(  200))                                             
      EQUIVALENCE(EM0063,GR(  201))                                             
      EQUIVALENCE(EM0064,GR(  202))                                             
      EQUIVALENCE(EM0065,GR(  203))                                             
      EQUIVALENCE(EM0066,GR(  204))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  231))                                             
      EQUIVALENCE(EM0068,GV(  222))                                             
      EQUIVALENCE(EM0069,GV(  221))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
      EQUIVALENCE(EM0136,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  867)=+EM0085                                                          
      A(  868)=+EM0088                                                          
      A(  869)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  870)=+EM0104                                                          
      A(  871)=+EM0105                                                          
      A(  872)=-EM0085                                                          
      A(  873)=-EM0088                                                          
      A(  874)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  875)=-EM0106                                                          
      A(  876)=-EM0107                                                          
      A(  877)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   65)=+EM0127                                                          
      SL(   65)=-EM0082                                                         
      A(  878)=+EM0086                                                          
      A(  879)=+EM0089                                                          
      A(  880)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  881)=+EM0130                                                          
      A(  882)=+EM0132                                                          
      A(  883)=-EM0086                                                          
      A(  884)=-EM0089                                                          
      A(  885)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  886)=-EM0133                                                          
      A(  887)=-EM0134                                                          
      A(  888)=-EM0135                                                          
      B(   66)=+EM0128                                                          
      SL(   66)=-EM0083                                                         
      A(  889)=+EM0087                                                          
      A(  890)=+EM0090                                                          
      A(  891)=+EM0093                                                          
      EM0137=                                   -EM0037                         
      A(  892)=+EM0136                                                          
      A(  893)=+EM0137                                                          
      A(  894)=-EM0087                                                          
      A(  895)=-EM0090                                                          
      A(  896)=-EM0093                                                          
      EM0139=              +EM0102*EM0068-EM0099*EM0069                         
      EM0140=              +EM0096*EM0069-EM0102*EM0067                         
      EM0141=              +EM0099*EM0067-EM0096*EM0068                         
      A(  897)=-EM0139                                                          
      A(  898)=-EM0140                                                          
      A(  899)=-EM0141                                                          
      B(   67)=+EM0129                                                          
      SL(   67)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0019                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  999))                                             
      EQUIVALENCE(EM0011,GR( 1000))                                             
      EQUIVALENCE(EM0012,GR( 1001))                                             
      EQUIVALENCE(EM0013,GR( 1002))                                             
      EQUIVALENCE(EM0014,GR( 1003))                                             
      EQUIVALENCE(EM0015,GR( 1004))                                             
      EQUIVALENCE(EM0016,GR( 1005))                                             
      EQUIVALENCE(EM0017,GR( 1006))                                             
      EQUIVALENCE(EM0018,GR( 1007))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  202))                                             
      EQUIVALENCE(EM0025,GR(  203))                                             
      EQUIVALENCE(EM0020,GR(  204))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   37))                                             
      EQUIVALENCE(EM0029,GR(   38))                                             
      EQUIVALENCE(EM0030,GR(   39))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  199))                                             
      EQUIVALENCE(EM0032,GR(  200))                                             
      EQUIVALENCE(EM0033,GR(  201))                                             
      EQUIVALENCE(EM0034,GR(  202))                                             
      EQUIVALENCE(EM0035,GR(  203))                                             
      EQUIVALENCE(EM0036,GR(  204))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  232))                                             
      EQUIVALENCE(EM0038,GV(  224))                                             
      EQUIVALENCE(EM0039,GV(  223))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR( 1044))                                             
      EQUIVALENCE(EM0041,GR( 1045))                                             
      EQUIVALENCE(EM0042,GR( 1046))                                             
      EQUIVALENCE(EM0043,GR( 1047))                                             
      EQUIVALENCE(EM0044,GR( 1048))                                             
      EQUIVALENCE(EM0045,GR( 1049))                                             
      EQUIVALENCE(EM0046,GR( 1050))                                             
      EQUIVALENCE(EM0047,GR( 1051))                                             
      EQUIVALENCE(EM0048,GR( 1052))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  196))                                             
      EQUIVALENCE(EM0055,GR(  197))                                             
      EQUIVALENCE(EM0050,GR(  198))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   31))                                             
      EQUIVALENCE(EM0059,GR(   32))                                             
      EQUIVALENCE(EM0060,GR(   33))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  193))                                             
      EQUIVALENCE(EM0062,GR(  194))                                             
      EQUIVALENCE(EM0063,GR(  195))                                             
      EQUIVALENCE(EM0064,GR(  196))                                             
      EQUIVALENCE(EM0065,GR(  197))                                             
      EQUIVALENCE(EM0066,GR(  198))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  211))                                             
      EQUIVALENCE(EM0068,GV(  200))                                             
      EQUIVALENCE(EM0069,GV(  199))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
      EQUIVALENCE(EM0136,EM0038)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  900)=+EM0085                                                          
      A(  901)=+EM0088                                                          
      A(  902)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  903)=+EM0104                                                          
      A(  904)=+EM0105                                                          
      A(  905)=-EM0085                                                          
      A(  906)=-EM0088                                                          
      A(  907)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  908)=-EM0106                                                          
      A(  909)=-EM0107                                                          
      A(  910)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   68)=+EM0127                                                          
      SL(   68)=-EM0082                                                         
      A(  911)=+EM0086                                                          
      A(  912)=+EM0089                                                          
      A(  913)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  914)=+EM0130                                                          
      A(  915)=+EM0132                                                          
      A(  916)=-EM0086                                                          
      A(  917)=-EM0089                                                          
      A(  918)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  919)=-EM0133                                                          
      A(  920)=-EM0134                                                          
      A(  921)=-EM0135                                                          
      B(   69)=+EM0128                                                          
      SL(   69)=-EM0083                                                         
      A(  922)=+EM0087                                                          
      A(  923)=+EM0090                                                          
      A(  924)=+EM0093                                                          
      EM0137=                                   -EM0037                         
      A(  925)=+EM0136                                                          
      A(  926)=+EM0137                                                          
      A(  927)=-EM0087                                                          
      A(  928)=-EM0090                                                          
      A(  929)=-EM0093                                                          
      EM0139=              +EM0102*EM0068-EM0099*EM0069                         
      EM0140=              +EM0096*EM0069-EM0102*EM0067                         
      EM0141=              +EM0099*EM0067-EM0096*EM0068                         
      A(  930)=-EM0139                                                          
      A(  931)=-EM0140                                                          
      A(  932)=-EM0141                                                          
      B(   70)=+EM0129                                                          
      SL(   70)=-EM0084                                                         
      RETURN                                                                    
      END                                                                       
      SUBROUTINE SH0089                                                         
      COMMON/PAR/GV(90000)                                                      
      COMMON/X/GR(90000)                                                        
      INCLUDE 'SLVL.INC'                                                        
      INCLUDE 'MLINK.INC'                                                       
C GENAZ                                                                         
C  GENAZ �����                                                                  
C  GENA                                                                         
      EQUIVALENCE(EM0010,GR(  999))                                             
      EQUIVALENCE(EM0011,GR( 1000))                                             
      EQUIVALENCE(EM0012,GR( 1001))                                             
      EQUIVALENCE(EM0013,GR( 1002))                                             
      EQUIVALENCE(EM0014,GR( 1003))                                             
      EQUIVALENCE(EM0015,GR( 1004))                                             
      EQUIVALENCE(EM0016,GR( 1005))                                             
      EQUIVALENCE(EM0017,GR( 1006))                                             
      EQUIVALENCE(EM0018,GR( 1007))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0024,GR(  202))                                             
      EQUIVALENCE(EM0025,GR(  203))                                             
      EQUIVALENCE(EM0020,GR(  204))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0028,GR(   37))                                             
      EQUIVALENCE(EM0029,GR(   38))                                             
      EQUIVALENCE(EM0030,GR(   39))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0031,GR(  199))                                             
      EQUIVALENCE(EM0032,GR(  200))                                             
      EQUIVALENCE(EM0033,GR(  201))                                             
      EQUIVALENCE(EM0034,GR(  202))                                             
      EQUIVALENCE(EM0035,GR(  203))                                             
      EQUIVALENCE(EM0036,GR(  204))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0037,GV(  233))                                             
      EQUIVALENCE(EM0038,GV(  226))                                             
      EQUIVALENCE(EM0039,GV(  225))                                             
C +EM0037+EM0038+EM0039+EM0067+EM0068+EM00                                      
C  GENGEO �����                                                                 
C  GENA                                                                         
      EQUIVALENCE(EM0040,GR( 1044))                                             
      EQUIVALENCE(EM0041,GR( 1045))                                             
      EQUIVALENCE(EM0042,GR( 1046))                                             
      EQUIVALENCE(EM0043,GR( 1047))                                             
      EQUIVALENCE(EM0044,GR( 1048))                                             
      EQUIVALENCE(EM0045,GR( 1049))                                             
      EQUIVALENCE(EM0046,GR( 1050))                                             
      EQUIVALENCE(EM0047,GR( 1051))                                             
      EQUIVALENCE(EM0048,GR( 1052))                                             
C  GENOM                                                                        
      EQUIVALENCE(EM0054,GR(  196))                                             
      EQUIVALENCE(EM0055,GR(  197))                                             
      EQUIVALENCE(EM0050,GR(  198))                                             
C   GENOM �����                                                                 
C  GENP                                                                         
      EQUIVALENCE(EM0058,GR(   31))                                             
      EQUIVALENCE(EM0059,GR(   32))                                             
      EQUIVALENCE(EM0060,GR(   33))                                             
C  GENP �����                                                                   
C GENV                                                                          
      EQUIVALENCE(EM0061,GR(  193))                                             
      EQUIVALENCE(EM0062,GR(  194))                                             
      EQUIVALENCE(EM0063,GR(  195))                                             
      EQUIVALENCE(EM0064,GR(  196))                                             
      EQUIVALENCE(EM0065,GR(  197))                                             
      EQUIVALENCE(EM0066,GR(  198))                                             
C GENV �����                                                                    
C  GENGEO                                                                       
      EQUIVALENCE(EM0067,GV(  212))                                             
      EQUIVALENCE(EM0068,GV(  202))                                             
      EQUIVALENCE(EM0069,GV(  201))                                             
C +EM0067+EM0068+EM0069+EM0028+EM0029+EM00                                      
C  GENGEO �����                                                                 
C VEKMIN                                                                        
C VEKMIN END                                                                    
C VEKSUM                                                                        
C VEKSUM END                                                                    
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0085,EM0010)                                                
      EQUIVALENCE(EM0088,EM0011)                                                
      EQUIVALENCE(EM0091,EM0012)                                                
      EQUIVALENCE(EM0086,EM0013)                                                
      EQUIVALENCE(EM0089,EM0014)                                                
      EQUIVALENCE(EM0092,EM0015)                                                
      EQUIVALENCE(EM0087,EM0016)                                                
      EQUIVALENCE(EM0090,EM0017)                                                
      EQUIVALENCE(EM0093,EM0018)                                                
      EQUIVALENCE(EM0104,EM0039)                                                
      EQUIVALENCE(EM0115,EM0112)                                                
      EQUIVALENCE(EM0116,EM0113)                                                
      EQUIVALENCE(EM0117,EM0114)                                                
C VEKMIN                                                                        
C VEKMIN END                                                                    
      EQUIVALENCE(EM0132,EM0037)                                                
C  GENA                                                                         
C  GENA                                                                         
      EM0070=+EM0040*EM0067+EM0043*EM0068+EM0046*EM0069                         
      EM0071=+EM0041*EM0067+EM0044*EM0068+EM0047*EM0069                         
      EM0072=+EM0042*EM0067+EM0045*EM0068+EM0048*EM0069                         
C VEKMIN                                                                        
      EM0073=                            +EM0058-EM0028                         
      EM0074=                            +EM0059-EM0029                         
      EM0075=                            +EM0060-EM0030                         
C VEKMIN END                                                                    
C VEKSUM                                                                        
      EM0076=                            +EM0073+EM0070                         
      EM0077=                            +EM0074+EM0071                         
      EM0078=                            +EM0075+EM0072                         
C VEKSUM END                                                                    
      EM0079=+EM0010*EM0076+EM0011*EM0077+EM0012*EM0078                         
      EM0080=+EM0013*EM0076+EM0014*EM0077+EM0015*EM0078                         
      EM0081=+EM0016*EM0076+EM0017*EM0077+EM0018*EM0078                         
C VEKMIN                                                                        
      EM0082=                            +EM0079-EM0037                         
      EM0083=                            +EM0080-EM0038                         
      EM0084=                            +EM0081-EM0039                         
C VEKMIN END                                                                    
      EM0094=+EM0085*EM0040+EM0088*EM0041+EM0091*EM0042                         
      EM0097=+EM0085*EM0043+EM0088*EM0044+EM0091*EM0045                         
      EM0100=+EM0085*EM0046+EM0088*EM0047+EM0091*EM0048                         
      EM0095=+EM0086*EM0040+EM0089*EM0041+EM0092*EM0042                         
      EM0098=+EM0086*EM0043+EM0089*EM0044+EM0092*EM0045                         
      EM0101=+EM0086*EM0046+EM0089*EM0047+EM0092*EM0048                         
      EM0096=+EM0087*EM0040+EM0090*EM0041+EM0093*EM0042                         
      EM0099=+EM0087*EM0043+EM0090*EM0044+EM0093*EM0045                         
      EM0102=+EM0087*EM0046+EM0090*EM0047+EM0093*EM0048                         
      A(  933)=+EM0085                                                          
      A(  934)=+EM0088                                                          
      A(  935)=+EM0091                                                          
      EM0105=                                   -EM0038                         
      A(  936)=+EM0104                                                          
      A(  937)=+EM0105                                                          
      A(  938)=-EM0085                                                          
      A(  939)=-EM0088                                                          
      A(  940)=-EM0091                                                          
      EM0106=              +EM0100*EM0068-EM0097*EM0069                         
      EM0107=              +EM0094*EM0069-EM0100*EM0067                         
      EM0108=              +EM0097*EM0067-EM0094*EM0068                         
      A(  941)=-EM0106                                                          
      A(  942)=-EM0107                                                          
      A(  943)=-EM0108                                                          
      EM0109=              -EM0020*EM0038+EM0025*EM0039                         
      EM0110=              +EM0020*EM0037-EM0024*EM0039                         
      EM0111=              -EM0025*EM0037+EM0024*EM0038                         
      EM0112=              -EM0020*EM0110+EM0025*EM0111                         
      EM0113=              +EM0020*EM0109-EM0024*EM0111                         
      EM0114=              -EM0025*EM0109+EM0024*EM0110                         
      EM0118=              -EM0050*EM0068+EM0055*EM0069                         
      EM0119=              +EM0050*EM0067-EM0054*EM0069                         
      EM0120=              -EM0055*EM0067+EM0054*EM0068                         
      EM0121=              -EM0050*EM0119+EM0055*EM0120                         
      EM0122=              +EM0050*EM0118-EM0054*EM0120                         
      EM0123=              -EM0055*EM0118+EM0054*EM0119                         
      EM0124=+EM0094*EM0121+EM0097*EM0122+EM0100*EM0123                         
      EM0125=+EM0095*EM0121+EM0098*EM0122+EM0101*EM0123                         
      EM0126=+EM0096*EM0121+EM0099*EM0122+EM0102*EM0123                         
C VEKMIN                                                                        
      EM0127=                            +EM0124-EM0115                         
      EM0128=                            +EM0125-EM0116                         
      EM0129=                            +EM0126-EM0117                         
C VEKMIN END                                                                    
      B(   71)=+EM0127                                                          
      SL(   71)=-EM0082                                                         
      A(  944)=+EM0086                                                          
      A(  945)=+EM0089                                                          
      A(  946)=+EM0092                                                          
      EM0130=                                   -EM0039                         
      A(  947)=+EM0130                                                          
      A(  948)=+EM0132                                                          
      A(  949)=-EM0086                                                          
      A(  950)=-EM0089                                                          
      A(  951)=-EM0092                                                          
      EM0133=              +EM0101*EM0068-EM0098*EM0069                         
      EM0134=              +EM0095*EM0069-EM0101*EM0067                         
      EM0135=              +EM0098*EM0067-EM0095*EM0068                         
      A(  952)=-EM0133                                                          
      A(  953)=-EM0134                                                          
      A(  954)=-EM0135                                                          
      B(   72)=+EM0128                                                          
      SL(   72)=-EM0083                                                         
      RETURN                                                                    
      END                                                                       
