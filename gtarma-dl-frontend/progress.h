#include <QObject>

class Progress : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float progressvalue READ progressvalue WRITE setProgressvalue NOTIFY progressvalueChanged)
    Q_PROPERTY(int progressCompletedCount READ progressCompletedCount WRITE setProgressCompletedCount NOTIFY progressCompletedCountChanged)
    Q_PROPERTY(int progressTotalCount READ progressTotalCount WRITE setProgressTotalCount NOTIFY progressTotalCountChanged)
    Q_PROPERTY(QString subtext READ subtext WRITE setSubtext NOTIFY subtextChanged)
public:
    void setProgressvalue(const float &value)
    {
        if (value != m_progressvalue)
        {
            m_progressvalue = value;
            emit progressvalueChanged();
        }
    }

    void setProgressCompletedCount(const int &value) {
        if (value != m_progressCompletedCount)
        {
            m_progressCompletedCount = value;
            emit progressCompletedCountChanged();
        }
    }

    void setProgressTotalCount(const int &value) {
        if (value != m_progressTotalCount)
        {
            m_progressTotalCount = value;
            emit progressTotalCountChanged();
        }
    }

    void setSubtext(const QString &value) {
        if (value != m_subtext)
        {
            m_subtext = value;
            emit subtextChanged();
        }
    }

    float progressvalue() const {
        return m_progressvalue;
    }

    int progressCompletedCount() const {
        return m_progressCompletedCount;
    }

    int progressTotalCount() const {
        return m_progressTotalCount;
    }

    QString subtext() const {
        return m_subtext;
    }

signals:
    void progressvalueChanged();
    void progressCompletedCountChanged();
    void progressTotalCountChanged();
    void subtextChanged();
private:
    float m_progressvalue;
    int m_progressCompletedCount;
    int m_progressTotalCount;
    QString m_subtext;
};
