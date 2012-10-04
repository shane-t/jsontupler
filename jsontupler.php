<?php

if (!(count($argv) > 1)) {
    die("provide output filename");
}

if (!file_exists($argv[1])) {
    $newfile = true;
    echo "- creating new file\n";
}

$fh = fopen($argv[1], 'a+');

if ($newfile) {
    echo "- beginning JSON\n";
    fwrite($fh, '
[');
    $first = true;
} else {
    $first = false;
}


$count = 0;

while ($question = readline('Key? > ')) {

    if ($question == 'end') break;
    
    $answer = readline('Value? > ');
    
    if ($first) {
        $json = "";
        $first = false;
    } else {
        $json = ",";
    }

    $json .= '
    { "' . addslashes($question) . '": "'. addslashes($answer) . '" }';
    
    fwrite($fh, $json);
    echo "wrote tuple " . $count ++ . "\n";
}

echo "- finished\n";

while ($answer = readline("Finalise? <Y/N> > ")) {
    if (in_array($answer, array("Y", "N"))) {
        if ($answer == "N") {
            echo "- not finalising\n";
            fclose($fh);
            break;
        } else {
            echo "- finalising\n";
            fwrite($fh, "
]");
            fclose($fh);
            break;
        }
    }
}



?>
