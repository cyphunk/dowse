#!/usr/bin/env zsh

polipo-conf() {
    func "generating base configuration for polipo"
    cat <<EOF
# own address (restricts to ipv4)
proxyAddress = "$dowse"
proxyName = "Dowse"

# allow local network
allowedClients = 127.0.0.1, $dowse_net

# avoid proxy users to see what others do
disableLocalInterface = true

# no disk cache
diskCacheRoot = ""

# no local web server
localDocumentRoot = ""

# make sure we are private
disableIndexing = true
disableServersList = true

# avoid ipv6 to go faster
dnsQueryIPv6 = no

# Uncomment this to disable Polipo's DNS resolver and use the system's
# default resolver instead.  If you do that, Polipo will freeze during
# every DNS query: (TODO: test and benchmark)
# dnsUseGethostbyname = yes
dnsNameServer = $dowse

daemonise = true

# to be specified by caller module
# pidFile = $dowse_path/log/polipo.pid
# logFile = $dowse_path/log/polipo.log

# to be tested
# disableVia=false
# censoredHeaders = from, accept-language
# censorReferer = maybe

# Uncomment this if you're paranoid.  This will break a lot of sites
# censoredHeaders = set-cookie, cookie, cookie2, from, accept-language
# censorReferer = true
EOF

}


polipo-start() {
    fn "polipo-start $*"
    conf=$1
    shift 1
    req=(conf)
    freq=($conf)
    ckreq

    pushd $dowse_path

    if [[ -z $root ]]; then
        polipo -c $conf $*
    else
        setuidgid $dowse_uid polipo -c $conf $*
    fi

    popd
}

polipo-stop() {
    fn polipo-stop
    pidfile=$1

    [[ -r $pidfile ]] || {
        warn "polipo not running"
        return 0
    }

    pushd $dowse_path

    pid=`cat $1`
    act "stopping polipo pid: ::1 pid::" $pid
    kill $pid
    waitpid $pid
#    rm -f "$pid"

    popd
}
