class IOWrapper
{
private:
  handle_t handle;
public:
  IOWrapper() = delete;
  IOWrapper(const IOWrapper& src) = delete;
  IOWrapper& operator=(const IOWrapper& src) = delete;
  ~IOWrapper()
  {
    if (handle != kNullHandle)
      raw_close(handle);
  }
  IOWrapper(IOWrapper&& src) : handle(src.handle)
  {
    src.handle = kNullHandle;
  }
  IOWrapper& operator=(IOWrapper&& src)
  {
    if(&src == this) return *this;
    if (handle != kNullHandle)
      raw_close(handle);

    handle = src.handle;
    src.handle = kNullHandle;
    return *this;
  }

  IOWrapper(handle_t const& handle1) : handle(handle1){};//!
  IOWrapper(handle_t && handle1) : handle(handle1){};

  void Write(const std::string& content)
  {
    raw_write(handle, content);
  }

};