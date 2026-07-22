# Güvenlik / Security

_Türkçe aşağıda — English below._

---

## Türkçe

### Güvenlik açığı bildirme

Bir güvenlik açığı bulduysanız lütfen **herkese açık bir issue açmayın**.
Bunun yerine GitHub'ın
[Private vulnerability reporting](https://github.com/Layellie/cppmaster-console/security/advisories/new)
özelliğini kullanın.

### Tek satırlık kurulum komutu hakkında

README'deki kurulum yöntemi şu biçimdedir:

```powershell
irm https://raw.githubusercontent.com/Layellie/cppmaster-console/master/install.ps1 | iex
```

Bu kalıp (`bir script indir ve doğrudan çalıştır`) yaygın olsa da, doğası
gereği **indirilen script'e tam güven** gerektirir. Kendi güvenliğiniz
için bilmeniz gerekenler:

- Script çalıştırmadan önce içeriğini okuyabilirsiniz:
  [`install.ps1`](install.ps1) — kısa ve tek işi var: GitHub Release'inden
  `CppMasterConsole.exe`'yi indirip `%LOCALAPPDATA%\CppMasterConsole`
  altına koyar ve çalıştırır.
- İndirilen `.exe`, bu deponun GitHub Actions iş akışı tarafından, kaynak
  koddan otomatik derlenir — elle yüklenmiş bir binary değildir. Hangi
  commit'ten derlendiği release açıklamasında yazar.
- Bu adımlara güvenmiyorsanız, depoyu klonlayıp kendiniz derleyin;
  README'de "Geliştirici olarak derleme" bölümü bunu anlatır.

### Uygulamanın eriştiği yerler

- Normal çalışmada yalnızca **çalışma dizinindeki `data/` alt klasörüne**
  yazar (ilerleme, ayarlar, başarımlar, yanlış kayıtları). `install.ps1`
  ile başlatıldığında bu klasör `%LOCALAPPDATA%\CppMasterConsole\data`
  olur.
- Tek istisna, Ayarlar menüsündeki **"İlerlemeyi dışa/içe aktar"**
  seçenekleridir: bunlar, sizin o anda elle girdiğiniz klasör yoluna
  yazar / o yoldan okur. Başka hiçbir yol kullanılmaz.
- Uygulamanın kendisi **hiçbir ağ bağlantısı kurmaz**, telemetri
  göndermez, sistem genelinde (kayıt defteri, PATH, servisler) hiçbir
  değişiklik yapmaz. Ağ erişimi yalnızca `install.ps1`'in indirme
  adımında olur.

---

## English

### Reporting a vulnerability

If you find a security issue, please **do not open a public issue**. Use
GitHub's
[private vulnerability reporting](https://github.com/Layellie/cppmaster-console/security/advisories/new)
instead.

### About the one-line install command

The install method in the README is:

```powershell
irm https://raw.githubusercontent.com/Layellie/cppmaster-console/master/install.ps1 | iex
```

While this pattern (download a script and execute it directly) is common,
it inherently requires **fully trusting the downloaded script**. For your
own safety:

- You can read the script before running it:
  [`install.ps1`](install.ps1) — it is short and does one thing: download
  `CppMasterConsole.exe` from the GitHub Release into
  `%LOCALAPPDATA%\CppMasterConsole` and run it.
- The downloaded `.exe` is built automatically from source by this
  repository's GitHub Actions workflow — it is not a hand-uploaded binary.
  The release notes state which commit it was built from.
- If you would rather not trust that chain, clone the repo and build it
  yourself; see "Geliştirici olarak derleme" (Building from source) in the
  README.

### What the application accesses

- During normal use it writes only to a `data/` subfolder **in its working
  directory** (progress, settings, achievements, mistake records). Launched
  via `install.ps1`, that resolves to
  `%LOCALAPPDATA%\CppMasterConsole\data`.
- The one exception is the **export/import progress** options in the
  Settings menu, which write to / read from a folder path *you* type in at
  that moment. No other paths are ever touched.
- The application itself makes **no network connections**, sends no
  telemetry, and changes nothing system-wide (no registry, PATH, or
  services). Network access happens only in `install.ps1`'s download step.
