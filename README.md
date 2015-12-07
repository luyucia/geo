## geo

geo is an extension for php.that can help you calculate the distance and encode longitude and latitude to geohash.


#install
```shell
phpize
./configure
make && make install

find your php.ini ,php.ini depends on your php.ini location
echo "extension=geo.so" >> php.ini
```

# distance
calculate the distance use Haversine formula
```php
  echo geo_distance(37.20251980382515,122.0664687799119,37.20253417575888,122.0664418307466);
```

# simplify distance
calculate the distance but it faster then geo_distance and lower percision
```php
  echo geo_simple_distance(37.20251980382515,122.0664687799119,37.20253417575888,122.0664418307466);
```

# geohash encode
geohash encode
```php
  echo geo_geohash_encode(122.0664687799119,37.20251980382515,20);
```

# geohash decode
geohash decode
```php
  var_dump(geo_geohash_decode('wwwg9sw06uk4u6un4mv9'));
```


### Introduce myself
I am a Chinese,and I have been at t com worked.

#geo extension 中文文档

## 距离计算
geo_simple_distance是简化版距离计算，速度快但是牺牲点精度

```php
  echo geo_simple_distance(37.20251980382515,122.0664687799119,37.20253417575888,122.0664418307466);
```

geo_distance采用Haversine算法（lucence默认距离算法），精度和时间比较适中

```php
  echo geo_distance(37.20251980382515,122.0664687799119,37.20253417575888,122.0664418307466);
```
## geohash 计算

编码解码geohash值
```php
  echo geo_geohash_encode(122.0664687799119,37.20251980382515,20);
  var_dump(geo_geohash_decode('wwwg9sw06uk4u6un4mv9'));
```

Thank you for your attention!
