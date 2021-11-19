
//                        -ASTROMETRIC DATA REDUCTION -
// THIS PROGRAM CALCULATES 8650-ASTEROID'S STANDART COORDINATES AND RMS VALUE USING PLATE CONSTANTS

 #include <stdio.h> 
 #include <math.h>
//
 const double a = 2.99932912482e-06; // Plate constants data 
 const double b = 6.74706357297e-09;
 const double c = -0.00307964542803;
 const double d = 5.04890402654e-09;
 const double e = -3.00379917347e-06;
 const double f = 0.0043560223034;

 // pixel coordinates of 8650 object - data comes from  : https://asteroid.lowell.edu/astfinder/ ( field alpha-delta )  --> DS9 ( pixel coordinates )
 const double x1 = 1098.11; 
 const double y2 = 1311.68;

 // Image's center alpha and delta values :
 const double alfa_deg = 124.868068092 ;
 const double dec_deg = 21.2672235071;
 const double alfa_ = 8.328326611;
 const double dec_ = 21.29141417;
 const double pi = 3.14159265359;
 const double pixel_scale = 0.6612428961660046;

int main()
   {

    double ra0, dec0, dec, alfa, X, Y, asteroid_alfa, asteroid_dec, rms, p, r, w;
    double x, y, error;

 // center alpha-delta
 ra0 = (alfa_deg*pi)/180;  //converting degree to radians
 printf("ra0 = %lf \n",ra0);
 dec0 = (dec_deg*pi)/180;
 printf("dec0 = %lf \n",dec0);
 alfa = (alfa_*pi)/180;
 dec = (dec_*pi)/180;

 // asteroidin pixel koordinatlarını ve görüntünün merkez alfa deltası kullanılarak
 // Standart Coordinates Equations : Ekvatoryal koordinat sisteminden (alfa,delta) standart koordinat sistemine dönüştürme (X,Y)
 p = cos(dec0)*cos(dec)*cos(alfa-ra0) + sin(dec0)*sin(dec);
 X = -(cos(dec)*sin(alfa-ra0))/p; 
 Y = -(sin(dec0)*cos(dec)*cos(alfa-ra0) - cos(dec0)*sin(dec))/p;

 //
 asteroid_alfa = alfa_deg + atan2(-1*X,(cos(dec0)-Y*sin(dec0)))*180/pi; 
 asteroid_dec = asin(((sin(dec0)+(Y*cos(dec0)))/sqrt(1+pow(X,2)+pow(Y,2))))*180/pi;

 //# .cor dosyasında index_ra,index_dec olarak verilen refarans yıldızlarının pixel koordinatlarını düzlem sabitleriyle hesaplama
 x = (e*(X-c) - b*(Y - f)) / (e*a - b*d); // hesaplanan (pixel) koordinatları bulunuyor
 y = (d*(X-c) - a*(Y - f)) / (d*b - a*e);

 // calculation of root mean square of 8650-ASTEROID
 //rms_err = hesaplanan pixel kordinatların ,CCD üzerinde pixel koordinatlara sahip cisimlerden ortalama olarak sapma miktarı(pixel)
 //error = hesaplanan pixel kordinatların gerçek pixel kordinatlardan ortalama olarak sapma miktarı(mas)
  r = x-x1;
  w = y-y2;
   rms = sqrt(r*r+w*w) ;
   error = rms * pixel_scale *1000;

 //results
 printf("Standart 'X' Coordinate of Asteroid  = %.lf \n",X) ;
 printf("Standart 'Y' Coordinate of Asteroid  = %.lf \n", Y);
 printf("8650-Asteroid * Right Ascension = %.lf \n", asteroid_alfa);
 printf("8650-Asteroid * Declination = %.lf \n",asteroid_dec);
 printf("rms = %.lf \n" , rms);
 printf("error = %.lf \n" , error);
return 0;
  }

/* OUTPUTS :
Standart 'X' Coordinate of Asteroid  = 0.000265898755026 
Standart 'Y' Coordinate of Asteroid  = 0.004262931070088 
Asteroid's Right Ascension = 124.8516927140 
Asteroid's Declination = 21.5114691879 
rms = 0.2447940065 */
