<?php

// total dataset * 
// % of total dataset represented in datapoint
$datapoints = [
  100, 62, 54, 160
];

// folks in dataset
$rows = 200;
$cols = count($datapoints);

$datasets = [];

for($i = 0; $i < $rows; $i++) {
  array_push($datasets, []);
}

foreach($datapoints as $stat) {
  for($i = 0; $i < $rows; $i++) {
    $datasets[$i][] = $i < $stat;
  }

  shuffle($datasets);
}

$export = "extern bool dataset[{$rows}][$cols] = {\n";
 
for($i = 0; $i < $rows - 1; $i++) {
  $export .= "\t" . str_replace([ '[', ']' ],[ '{', '}' ],json_encode($datasets[$i]));

  if($i !== $rows - 2)
    $export .= ",\n";
  else 
    $export .= "\n";
}
foreach($datasets as $person) {
}

$export .= "};";

file_put_contents("./src/main/dataset.h", $export);

echo "Done.\n";

exit(0);
