#include "StdoutCapture.h"

StdCapture::StdCapture()
    : m_oldStdOut(0)
    , m_oldStdErr(0)
    , m_capturing(false)
    , m_init(false)
{
    m_pipe[READ] = 0;
    m_pipe[WRITE] = 0;
    if (_pipe(m_pipe, 65536, O_BINARY) == -1)
        return;
    m_oldStdOut = dup(fileno(stdout));
    m_oldStdErr = dup(fileno(stderr));
    if (m_oldStdOut == -1 || m_oldStdErr == -1)
        return;
    m_init = true;
}

StdCapture::~StdCapture()
{
    if (m_capturing)
        EndCapture();
    if (m_oldStdOut > 0)
        close(m_oldStdOut);
    if (m_oldStdErr > 0)
        close(m_oldStdErr);
    if (m_pipe[READ] > 0)
        close(m_pipe[READ]);
    if (m_pipe[WRITE] > 0)
        close(m_pipe[WRITE]);
}

void StdCapture::BeginCapture()
{
    if (!m_init)
        return;
    if (m_capturing)
        EndCapture();
    fflush(stdout);
    fflush(stderr);
    dup2(m_pipe[WRITE], fileno(stdout));
    dup2(m_pipe[WRITE], fileno(stderr));
    m_capturing = true;
}

bool StdCapture::EndCapture()
{
    if (!m_init)
        return false;
    if (!m_capturing)
        return false;
    fflush(stdout);
    fflush(stderr);
    dup2(m_oldStdOut, fileno(stdout));
    dup2(m_oldStdErr, fileno(stderr));
    m_captured.clear();
    std::string buf;
    const int bufSize = 1024;
    buf.resize(bufSize);
    int bytesRead = 0;
    if (!eof(m_pipe[READ]))
    {
        bytesRead = read(m_pipe[READ], &(*buf.begin()), bufSize);
    }
    while(bytesRead == bufSize)
    {
        m_captured += buf;
        bytesRead = 0;
        if (!eof(m_pipe[READ]))
        {
            bytesRead = read(m_pipe[READ], &(*buf.begin()), bufSize);
        }
    }
    if (bytesRead > 0)
    {
        buf.resize(bytesRead);
        m_captured += buf;
    }
    return true;
}

std::string StdCapture::GetCapture() const
{
    std::string::size_type idx = m_captured.find_last_not_of("\r\n");
    if (idx == std::string::npos)
        return m_captured;
    else
        return m_captured.substr(0, idx+1);
}

StdCapture &StdCapture::getInstance()
{
    static StdCapture ins;
    return ins;
}

void StdCapture::start()
{
    getInstance().BeginCapture();
}

void StdCapture::stop()
{
    getInstance().EndCapture();
}

QString StdCapture::get()
{
    return QString::fromStdString(getInstance().GetCapture());
}
