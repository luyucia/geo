<?php

function getDistanceSimplify($longitudeA,$latitudeA,$longitudeB,$latitudeB)
{
    $dx = $longitudeA - $longitudeB;//经度差
    $dy = $latitudeA  - $latitudeB;  //纬度差
    $b  = ($latitudeA + $latitudeB) / 2.0; //平均纬度
    $Lx = deg2rad($dx) * 6367000.0 * cos( deg2rad($b) ); //东西距离
    $Ly = deg2rad($dy) * 6367000.0 ; //南北距离
    return sqrt($Lx * $Lx + $Ly * $Ly);

}

echo geo_simple_distance(37.20251980382515,122.0664687799119,37.20253417575888,122.0664418307466);
echo "\n";
echo geo_distance(37.20251980382515,122.0664687799119,37.20253417575888,122.0664418307466);
echo "\n";
echo getDistanceSimplify(37.20251980382515,122.0664687799119,37.20253417575888,122.0664418307466);
echo "\n";


$start = microtime(true);
for ($i=0; $i < 100000; $i++) {
    getDistanceSimplify(37.20251980382515,122.0664687799119,37.20253417575888,122.0664418307466);
}
echo microtime(true) - $start;
echo "\n";

$start = microtime(true);
for ($i=0; $i < 100000; $i++) {
    geo_distance(37.20251980382515,122.0664687799119,37.20253417575888,122.0664418307466);
}
echo microtime(true) - $start;
echo "\n";

$start = microtime(true);
for ($i=0; $i < 100000; $i++) {
    geo_simple_distance(37.20251980382515,122.0664687799119,37.20253417575888,122.0664418307466);
}
echo microtime(true) - $start;

echo "\n";
echo geo_geohash_encode(122.0664687799119,37.20251980382515,9);
var_dump(geo_geohash_decode('wwwg9sw06uk4u6un4mv9'));
?>
