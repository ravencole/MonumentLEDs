<?php

$total = 200;

$datapoints = [
  100, 62, 54, 160
];

$datasets = [];

for($i = 0; $i < $total; $i++) {
  array_push($datasets, []);
}

foreach($datapoints as $stat) {
  for($i = 0; $i < $total; $i++) {
    $datasets[$i][] = $i < $stat;
  }

  shuffle($datasets);
}
 
foreach($datasets as $person) {
  echo str_replace([ '[', ']' ],[ '{', '}' ],json_encode($person) . ",\n");
}

