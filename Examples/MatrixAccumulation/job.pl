#!/usr/bin/perl
my $nruns=20;
my $nkernels=12;
for my $i (12) {#(0..12) { #(0..$nkernels) {
for my $m (0,1,2) {
    print STDERR "KERNEL=$i, MODE=$m\n";
    print "KERNEL=$i, MODE=$m\t";
    my $r=($i==0)?2:0;
    system("scons -s kernel=$i ref=$r v=0 mode=$m");
    for my $run (0..$nruns) {
    my $res=`./matacc$i`;
    print "$res\t" unless $run==0;
    }
    print "\n";
    if ($i==0) {last;}
}
}
