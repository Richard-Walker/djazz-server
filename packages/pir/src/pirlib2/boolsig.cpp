#include "boolsig.h"


BoolSig::BoolSig() :
    m_Sig(false)
{
    pthread_mutex_init(&m_Mutex,0);
    pthread_cond_init(&m_Cond,0);
}

BoolSig::~BoolSig()
{
    pthread_mutex_destroy(&m_Mutex);
    pthread_cond_destroy(&m_Cond);
}

void BoolSig::broadcast( bool sig )
{
    pthread_mutex_lock(&m_Mutex);
    m_Sig = sig;
    pthread_mutex_unlock(&m_Mutex);
    pthread_cond_broadcast(&m_Cond);
}

void BoolSig::signal( bool sig )
{
    pthread_mutex_lock(&m_Mutex);
    m_Sig = sig;
    pthread_mutex_unlock(&m_Mutex);
    pthread_cond_signal(&m_Cond);
}

bool BoolSig::wait()
{
   bool res = false;
   pthread_mutex_lock(&m_Mutex);
   if ( m_Sig ) 
   {
      pthread_mutex_unlock(&m_Mutex);      
      return true;
   }
   pthread_cond_wait(&m_Cond, &m_Mutex);
   res = m_Sig;
   pthread_mutex_unlock(&m_Mutex);
   return res;
}
