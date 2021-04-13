<?php

// total dataset * 
// % of total dataset represented in datapoint
$datapoints = [
  100, // POC
  62,  // Over 60
  54,  // From Philly
  160  // Mothers and Grandmothers
];

// folks in dataset
$rows = 200;
// # of datapoints
$cols = count($datapoints);

$datasets = [];

for($i = 0; $i < $rows; $i++) 
  array_push($datasets, []);

foreach($datapoints as $stat) {
  for($i = 0; $i < $rows; $i++) 
    $datasets[$i][] = $i < $stat;

  shuffle($datasets);
}

function prepareLine($line) {
  return "\t" . str_replace(
    [ '[', ']' ],
    [ '{', '}' ],
    json_encode($line)
  );
}

$export = "extern bool dataset[{$rows}][$cols] = {\n";
 
for($i = 0; $i < $rows - 1; $i++) {
  $last_line = $i === $rows - 2;

  $export .= prepareLine($datasets[$i])
    . ($last_line ? "\n" : ",\n");
}

$export .= "};\n";

file_put_contents("./main/dataset.h", $export);

echo "Done.\n";

exit(0);
