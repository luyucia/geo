#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653
#define dutorad(X) ((X)/180*PI)
#define radtodu(X) ((X)/PI*180)
#define EARTH_RADIUS 6378137

double radian(double d);
double radian(double d)
{
    return d * PI / 180.0;
}

typedef struct {
    double latitude,longitude;
} coord_struct;
char base32[]="0123456789bcdefghjkmnpqrstuvwxyz";
int bits[]={16,8,4,2,1};

double simple_distance(double latitudeA,double longitudeA,double latitudeB,double longitudeB)
{
    double dx;
    double dy;
    double b;
    double lx;
    double ly;
    dx = latitudeA - latitudeB;
    dy = longitudeA  - longitudeB;
    b = (longitudeA + longitudeB) / 2.0;
    lx = dutorad(dx) * EARTH_RADIUS * cos( dutorad(b) );
    ly = dutorad(dy) * EARTH_RADIUS;
    return sqrt(lx*lx+ly*ly);
}

double get_distance(double lat1, double lng1, double lat2, double lng2)
{
    double radLat1 = radian(lat1);
    double radLat2 = radian(lat2);
    double a = radLat1 - radLat2;
    double b = radian(lng1) - radian(lng2);

    double dst = 2 * asin((sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2) )));

    dst = dst * EARTH_RADIUS;
    //dst= round(dst * 10) / 10;
    return dst;
}

const char* geohash_encode(double latitude, double longitude, int precision) {
    double lat_interval[]={-90.0,90.0};
    double lon_interval[]={-180.0,180.0};
    int bit,ch,i;
    bit=ch=i=0;
    int is_even=1;
    double mid;
    //static char geohash[50]="";
    char *geohash="";
    while(i<precision){
        if(is_even){
            mid = (lon_interval[0]+lon_interval[1])/2.0;
            if(longitude>mid){
                ch |=bits[bit];
                lon_interval[0]=mid;
            }else{
                lon_interval[1]=mid;
            }
        }else{
            mid=(lat_interval[0]+lat_interval[1])/2.0;
            if(latitude>mid){
                ch |=bits[bit];
                lat_interval[0]=mid;
            }else{
                lat_interval[1] = mid;
            }
        }
        is_even=!is_even;
        if(bit < 4){
            bit++;
        }else{
            i++;
            spprintf(&geohash, 0, "%s%c",geohash, base32[ch]);
            //zend_printf("%s\n",geohash);
            //sprintf(geohash,"%s%c",geohash, base32[ch]);
            //zend_printf("%s\n",geohash);

            bit=0;
            ch=0;
        }

    }
    return geohash;
}

unsigned int str_position(char needle, char *string) {
    int pos = -1;
    int length = strlen(string);
    int i;
    for(i = 0; i < length; i++) {
        if(needle == string[i]) {
            pos = i;
            break;
        }

    }

    return pos;
}

coord_struct geohash_decode(char *hash) {
    double lat_interval[]={-90.0,90.0};
    double lon_interval[]={-180.0,180.0};
    int hash_length=strlen(hash);
    int is_even=1;
    int str_postion = 0;
    double result[2];
    int i,j;
    for ( i = 0; i < hash_length; ++i){
        str_postion=str_position(hash[i], base32);
        for ( j = 0; j < 5; ++j){
            if(is_even){
                lon_interval[!(str_postion&bits[j])] =  (lon_interval[0]+lon_interval[1])/2.0;
            }else{
                lat_interval[!(str_postion&bits[j])] =  (lat_interval[0]+lat_interval[1])/2.0;
            }
            is_even=!is_even;
        }
    }
    coord_struct coord_result;
    coord_result.latitude=(lat_interval[0] + lat_interval[1]) / 2;
    coord_result.longitude=(lon_interval[0] + lon_interval[1]) / 2;
    //zend_printf("%f,%f\n",coord_result.latitude,coord_result.longitude );
    return coord_result;
}
