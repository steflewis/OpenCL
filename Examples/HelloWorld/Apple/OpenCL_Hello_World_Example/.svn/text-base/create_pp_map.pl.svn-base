while (<>) {

    my $w=$_;
    chomp $w;
    $w=~s/^.*define.//;
    $w=~s/\s+.*$//;
    print "info[\"$w\"]=InfoTuple($w,UINT);\n";
}
