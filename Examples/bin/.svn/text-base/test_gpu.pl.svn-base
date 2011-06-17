#!/usr/bin/perl
my $gpu='';
if (-x 'lspci') {
    $gpu=`lspci -v | grep VGA`;
} else { # assumme it's a Mac
    $gpu='NVIDIA';#`system_profiler -detailLevel mini | grep Chipset`;
}
if ($gpu=~/nVidia/i ) {
print 'NVIDIA';
} elsif (
$gpu=~/AMD/i ) { # bogus, but I don't know what would be OK
print 'AMD';
} else {
    print 'NONE';
}
