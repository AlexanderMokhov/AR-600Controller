      FUNCTION FUZ018(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    бедро'                                  
      EQUIVALENCE (PAR01,GV(  1508))
      EQUIVALENCE (PAR02,GV(  1509))
      EQUIVALENCE (PAR03,GV(  1510))
      YO=PAR01*Y
      XO=PAR02*X+PAR03
      FUZ018=XO+YO
      RETURN
      END

      FUNCTION FUY015(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    бедро 1'                                
      EQUIVALENCE (PAR01,GV(  1511))
      EQUIVALENCE (PAR02,GV(  1512))
      EQUIVALENCE (PAR03,GV(  1513))
      YO=PAR01*Y
      XO=PAR02*X+PAR03
      FUY015=XO+YO
      RETURN
      END

      FUNCTION FUX016(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    бедро 2'                                
      EQUIVALENCE (PAR01,GV(  1514))
      EQUIVALENCE (PAR02,GV(  1515))
      EQUIVALENCE (PAR03,GV(  1516))
      YO=PAR01*Y
      XO=PAR02*X+PAR03
      FUX016=XO+YO
      RETURN
      END

      FUNCTION FUY009(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    лев рука 5'                             
      EQUIVALENCE (PAR01,GV(  1517))
      EQUIVALENCE (PAR02,GV(  1518))
      EQUIVALENCE (PAR03,GV(  1519))
      YO=PAR01*Y
      XO=PAR02*X+PAR03
      FUY009=XO+YO
      RETURN
      END

      FUNCTION FUX023(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    stopa ugol'                             
      EQUIVALENCE (PAR01,GV(  1520))
      EQUIVALENCE (PAR02,GV(  1521))
      YO=PAR01*Y
      XO=PAR02*X
      FUX023=XO+YO
      RETURN
      END

      FUNCTION FUY023(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    stopa ugol'                             
      EQUIVALENCE (PAR01,GV(  1522))
      EQUIVALENCE (PAR02,GV(  1523))
      YO=PAR01*Y
      XO=PAR02*X
      FUY023=XO+YO
      RETURN
      END

      FUNCTION FUZ023(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    stopa ugol'                             
      EQUIVALENCE (PAR01,GV(  1524))
      EQUIVALENCE (PAR02,GV(  1525))
      YO=PAR01*Y
      XO=PAR02*X
      FUZ023=XO+YO
      RETURN
      END

      FUNCTION FUX022(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    прав рука 4                             
      EQUIVALENCE (PAR01,GV(  1526))
      EQUIVALENCE (PAR02,GV(  1527))
      EQUIVALENCE (PAR03,GV(  1528))
      YO=PAR01*Y
      XO=PAR02*X+PAR03
      FUX022=XO+YO
      RETURN
      END

      FUNCTION FUZ011(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    шея 2'                                  
      EQUIVALENCE (PAR01,GV(  1529))
      EQUIVALENCE (PAR02,GV(  1530))
      EQUIVALENCE (PAR03,GV(  1531))
      YO=PAR01*Y
      XO=PAR02*X+PAR03
      FUZ011=XO+YO
      RETURN
      END

      FUNCTION FUX012(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    голова 1'                               
      EQUIVALENCE (PAR01,GV(  1532))
      EQUIVALENCE (PAR02,GV(  1533))
      EQUIVALENCE (PAR03,GV(  1534))
      YO=PAR01*Y
      XO=PAR02*X+PAR03
      FUX012=XO+YO
      RETURN
      END

      FUNCTION FUY013(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    голова 2'                               
      EQUIVALENCE (PAR01,GV(  1535))
      EQUIVALENCE (PAR02,GV(  1536))
      EQUIVALENCE (PAR03,GV(  1537))
      YO=PAR01*Y
      XO=PAR02*X+PAR03
      FUY013=XO+YO
      RETURN
      END

      FUNCTION FUY017(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    колено'                                 
      EQUIVALENCE (PAR01,GV(  1538))
      EQUIVALENCE (PAR02,GV(  1539))
      EQUIVALENCE (PAR03,GV(  1540))
      YO=PAR01*Y
      XO=PAR02*X+PAR03
      FUY017=XO+YO
      RETURN
      END

      FUNCTION FUX008(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    лев рука 4'                             
      EQUIVALENCE (PAR01,GV(  1541))
      EQUIVALENCE (PAR02,GV(  1542))
      EQUIVALENCE (PAR03,GV(  1543))
      YO=PAR01*Y
      XO=PAR02*X+PAR03
      FUX008=XO+YO
      RETURN
      END

      FUNCTION FUY032(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    default nam                             
      EQUIVALENCE (PAR01,GV(  1544))
      EQUIVALENCE (PAR02,GV(  1545))
      YO=PAR01*Y
      XO=PAR02*X
      FUY032=XO+YO
      RETURN
      END

      FUNCTION FUZ014(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    тело'                                   
      EQUIVALENCE (PAR01,GV(  1546))
      EQUIVALENCE (PAR02,GV(  1547))
      EQUIVALENCE (PAR03,GV(  1548))
      YO=PAR01*Y
      XO=PAR02*X+PAR03
      FUZ014=XO+YO
      RETURN
      END

      FUNCTION FUY010(X,Y,XO,YO)
      COMMON /PAR/ gv(90000)
C    шея 1'                                  
      EQUIVALENCE (PAR01,GV(  1549))
      EQUIVALENCE (PAR02,GV(  1550))
      EQUIVALENCE (PAR03,GV(  1551))
      YO=PAR01*Y
      XO=PAR02*X+PAR03
      FUY010=XO+YO
      RETURN
      END

      FUNCTION PLZ001(T)
      COMMON /PAR/gv(90000)

C     default name                            

      EQUIVALENCE (PAR01,GV(  1552))
      PLZ001=PAR01
      RETURN
      END

      FUNCTION PLZ002(T)
      COMMON /PAR/gv(90000)

C     default name                            

      EQUIVALENCE (PAR01,GV(  1553))
      PLZ002=PAR01
      RETURN
      END

      FUNCTION PLZ003(T)
      COMMON /PAR/gv(90000)

C     default name                            

      EQUIVALENCE (PAR01,GV(  1554))
      PLZ003=PAR01
      RETURN
      END

      FUNCTION PLZ004(T)
      COMMON /PAR/gv(90000)

C     default name                            

      EQUIVALENCE (PAR01,GV(  1555))
      PLZ004=PAR01
      RETURN
      END

