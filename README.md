## geo

geo is an extension for php.that can help you calculate the distance and encode longitude and latitude to geohash

# distance
calculate the distance
```php
  echo geo_distance(37.20251980382515,122.0664687799119,37.20253417575888,122.0664418307466);
```

# simplify distance
calculate the distance but it faster then geo_distance and lower percision
```php
  echo geo_simple_distance(37.20251980382515,122.0664687799119,37.20253417575888,122.0664418307466);
```

# geohahs encode
geohahs encode
```php
  echo geo_geohash_encode(122.0664687799119,37.20251980382515,20);
```

# geohahs decode
geohahs decode
```php
  var_dump(geo_geohash_decode('wwwg9sw06uk4u6un4mv9'));
```

Thank you for attention!
